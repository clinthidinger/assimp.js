/*jslint nomen: true, debug: true, evil: false, vars: true, white: true, browser: true, plusplus: true */
/*global ASSIMPJS, THREE */
var AssimpToThreeJS = (function() {

    'use strict';
    //var camera = new THREE.PerspectiveCamera( 70, window.innerWidth / window.innerHeight, 1, 1000 );
    //camera.position.z = 400;

    function getPolyTriCount(numVerts) {
        if (numVerts < 3) {
            return 0;
        }
        return (numVerts - 2);
    }

    function getMeshTriCount(mesh) {

        var face,
            faceIdx = 0,
            numIndices = 0,
            triCount = 0,
            numFaces = mesh.getNumFaces();

        for (faceIdx = 0; faceIdx < numFaces; ++faceIdx) {
            face = mesh.getFace(faceIdx);
            numIndices = face.getNumIndices();
            triCount += getPolyTriCount(numIndices);
        }

        return triCount;
    }

    function triangulatePoly(indices) {
        // Also, check https://threejsdoc.appspot.com/doc/three.js/src.source/extras/geometries/TextGeometry.js.html
        //assert( orderedPointCount >= 3 );
        var triCount = getPolyTriCount(indices.length),
            tris = Array(triCount),
            orderedPointCount = indices.length,
            offsetIndex = 0,
            base0 = 0 + offsetIndex,
            base1 = 1 + offsetIndex,
            lastTri = triCount - 1,
            vtxIdx,
            revVtxIdx,
            triIdx = 0,
            tri,
            nextTri;

        for (vtxIdx = 0, revVtxIdx = orderedPointCount - 1, triIdx = 0; triIdx < triCount;) {
            tri = [base0, base1, base1 + 1];
            tris[triIdx] = [indices[tri[0]], indices[tri[1]], indices[tri[2]]];
            ++triIdx;
            if (triIdx <= lastTri) {
                nextTri = [tri[2], offsetIndex + revVtxIdx--, tri[0]];
                tris[triIdx] = [indices[nextTri[0]], indices[nextTri[1]], indices[nextTri[2]]];
                base0 = nextTri[1];
                base1 = nextTri[0];
                ++triIdx;
            }
        } // end for

        return tris;
    }

    //function loadVertexAttribute3(mesh, array, bufferAttr, numVertices) {
    //  for ( var vertIdx = 0; vertIdx < numVertices; ++vertIdx ) {
    //    var v = array[vertIdx];
    //    bufferAttr.setXYZ( vertIdx, v.getX(), v.getY(), v.getZ() );
    //  }
    //}

    function loadPositions(mesh, geom) {

        var numVertices = mesh.getNumVertices(),
            vertexPosAttr,
            vertIdx,
            pos;

        //positions = mesh.getVertices();
        vertexPosAttr = new THREE.BufferAttribute(new Float32Array(numVertices * 3), 3);
        for (vertIdx = 0; vertIdx < numVertices; ++vertIdx) {
            pos = mesh.getVertex(vertIdx); //positions[vertIdx];
            vertexPosAttr.setXYZ(vertIdx, pos.getX(), pos.getY(), pos.getZ());
        }
        geom.addAttribute('position', vertexPosAttr);
    }

    function loadTriIndices(mesh, geom) {
          var triCount,
            face,
            triIndicesAttr,
            faceIdx,
            indexIdx;
            
        triCount = mesh.getNumFaces();
        triIndicesAttr = new THREE.BufferAttribute(new Uint16Array(triCount * 3), 1); // check if greater than max uint16
        indexIdx = 0;
        
        for (faceIdx = 0; faceIdx < triCount; ++faceIdx) {
            face = mesh.getFace(faceIdx);
            triIndicesAttr.array[indexIdx++] = face.getIndex(0);
            triIndicesAttr.array[indexIdx++] = face.getIndex(1);
            triIndicesAttr.array[indexIdx++] = face.getIndex(2);
        }
        
        geom.setIndex(triIndicesAttr);
    }
    
    function loadPolyIndices(mesh, geom) {

        var i,
            primType,
            numFaces,
            faces,
            triCount,
            face,
            numIndices,
            triIndicesAttr,
            faceTriIdx,
            indexIdx,
            faceIdx,
            indices = [],
            polyTriCount,
            tris,
            triIdx,
            tri;

        numFaces = mesh.getNumFaces();
        triCount = getMeshTriCount(mesh);
        triIndicesAttr = new THREE.BufferAttribute(new Uint16Array(triCount * 3), 1); // check if greater than max uint16
        faceTriIdx = 0;
        indexIdx = 0;
        
        for (faceIdx = 0; faceIdx < numFaces; ++faceIdx) {

            face = mesh.getFace(faceIdx);
            numIndices = face.getNumIndices();
            indices.length = numIndices;
            for (i = 0; i < numIndices; ++i) {
                indices[i] = face.getIndex(i);
            }
            tris = triangulatePoly(indices);
            polyTriCount = tris.length;

            for (triIdx = 0; triIdx < polyTriCount; ++triIdx) {
                tri = tris[triIdx];
                triIndicesAttr.array[indexIdx++] = tri[0];
                triIndicesAttr.array[indexIdx++] = tri[1];
                triIndicesAttr.array[indexIdx++] = tri[2];
            }
        }
    
        geom.setIndex(triIndicesAttr);
    }

    function loadNormals(mesh, geom) {

        var numVertices = mesh.getNumVertices(),
            vertexNrmAttr = new THREE.BufferAttribute(new Float32Array(numVertices * 3), 3),
            vertIdx,
            nrm;

        for (vertIdx = 0; vertIdx < numVertices; ++vertIdx) {
            nrm = mesh.getNormal(vertIdx); //normals[vertIdx];
            vertexNrmAttr.setXYZ(vertIdx, nrm.getX(), nrm.getY(), nrm.getZ());
        }
        geom.addAttribute('normal', vertexNrmAttr);
    }

    function loadVertexColors(mesh, geom, colorSetIdx) {

        var numVertices = mesh.getNumVertices(),
            vertexClrAttr = new THREE.BufferAttribute(new Float32Array(numVertices * 3), 3),
            vertIdx,
            clr;

        for (vertIdx = 0; vertIdx < numVertices; ++vertIdx) {
            clr = mesh.getColor(colorSetIdx, vertIdx);
            vertexNrmAttr.setXYZ(vertIdx, clr.getX(), clr.getY(), clr.getZ());
        }
        geom.addAttribute('color', vertexClrAttr);
    }

    function loadTextureCoords(mesh, geom, index) {

        var numVertices = mesh.getNumVertices(),
            textureCoordAttr = new THREE.BufferAttribute(new Float32Array(numVertices * 2), 2),
            vertIdx,
            uv;

        if (index > 1) {
            // Error. Only 2 sets supported.
            return;
        }

        for (vertIdx = 0; vertIdx < numVertices; ++vertIdx) {
            uv = mesh.getTextureCoord(index, vertIdx);
            textureCoordAttr.setXY(vertIdx, uv.getX(), uv.getY());
        }

        if (index === 1) {
            geom.addAttribute('uv2', textureCoordAttr);
        } else {
            geom.addAttribute('uv', textureCoordAttr);
        }
    }

    function loadBones(mesh, geom) {

        //var bones = mesh.getBones(),
        var numBones = mesh.getNumBones(),
            boneIdx,
            bone,
            numWeights,
            weights,
            wtIdx,
            weight,
            mtx;

        for (boneIdx = 0; boneIdx < numBones; ++boneIdx) {
            bone = mesh.getBone(boneIdx);
            numWeights = bone.getNumWeights();
            weights = bone.getWeights();
            for (wtIdx = 0; wtIdx < numWeights; ++wtIdx) {
                weight = weights[weightIdx];
                //weight.getVertexId();
                //weight.getWeight();
            }
            mtx = bone.getOffsetMatrix();
        }
    }

    function loadMesh(threeScene, mesh) {
        // see BufferGeometry.js fromDirectGeometry()

        var geom,
            name,
            matIdx,
            primType,
            numColorChannels,
            numUVChannels,
            threeMesh;

        geom = new THREE.BufferGeometry();
        name = mesh.getName();
        matIdx = mesh.getMaterialIndex();
        primType = mesh.getPrimitiveTypes();

        geom.addAttribute('name', name);
        geom.addAttribute('material_index', matIdx);

        if (!mesh.hasPositions() || !mesh.hasFaces()) {
            return geom;
        }

        loadPositions(mesh, geom);
        
        if (primType === Module.aiPrimitiveType.TRIANGLE.value) {
            loadTriIndices(mesh, geom);
        }
        else if (primType === Module.aiPrimitiveType.POLYGON.value) {
            loadPolyIndices(mesh, geom);
        }
        else {
            // Unsupported type.
            console.log('Unsupported type: ' + primType);
            return;
        }

        if (mesh.hasNormals()) {
            loadNormals(mesh, geom);
        }

        if (mesh.hasTangentsAndBitangents()) {
            //tangents = mesh.getTangents();
            //bitangents = mesh.getBitangents();
        }

        if (mesh.hasVertexColors(0)) {
            loadVertexColors(mesh, geom, 0);
        }

        if (mesh.hasTextureCoords(0)) {
            //numUVChannels = mesh.GetNumUVChannels();
            loadTextureCoords(mesh, geom, 0);
        }

        if (mesh.hasTextureCoords(1)) {
            loadTextureCoords(mesh, geom, 1);
        }

        if (mesh.hasBones()) {
            loadBones(mesh, geom);
        }

        //material = new THREE.MeshBasicMaterial({
        //        color: 0x000000,
        //        wireframe: true,
        //        wireframeLinewidth: 2
        //    });

        threeMesh = new THREE.Mesh(geom);


        threeScene.add(threeMesh);
    }

    function loadContents(contents) {
        var i = 0;

        var threeScene = new THREE.Scene();
        var importer = new Module.Importer();
        var assimpScene = importer.readFileFromMemory(contents, Module.GetTargetRealtimeMaxQualityFlags());

        var numMeshes = assimpScene.getNumMeshes();
        var numMaterials = assimpScene.getNumMaterials();
        var numLights = assimpScene.getNumLights();
        var numAnimations = assimpScene.getNumAnimations();
        var numTextures = assimpScene.getNumTextures();
        var numCameras = assimpScene.getNumCameras();


        for (i = 0; i < numMaterials; ++i) {
            var mat = assimpScene.getMaterial(i);
        }

        for (i = 0; i < numMeshes; ++i) {
            var mesh = assimpScene.getMesh(i);
            loadMesh(threeScene, mesh);
            //scene.add(mesh);
            // how to do sub meshes???
        }

        for (i = 0; i < numTextures; ++i) {
            var texture = assimpScene.getTexture(i);
        }
        for (i = 0; i < numLights; ++i) {
            var light = assimpScene.getLight(i);
        }
        for (i = 0; i < numAnimations; ++i) {
            var animation = assimpScene.getAnimation(i);
        }
        for (i = 0; i < numCameras; ++i) {
            var camera = assimpScene.getCamera(i);
        }

        importer.delete();
        //var format = "collada"; //! @see Exporter.cpp line 98 for supported formats.
        //var outStr = exporter.exportToString(scene, format, null);
        //var h = 0;
        return threeScene;
    }


    //////////=======================================================

    function savePositions(threeMesh, assimpMesh) {
        var positions = threeMesh.geometry.getAttribute('position');
        var numVertices = positions.count;
        assimpMesh.allocateVertices(numVertices);
        //var assimpVtx = new Module.aiVector3D();
        
        
        //assert(positions.array.length === numVertices);
        //var len = positions.array.length;
        //var n = assimpMesh.getNumVertices();
        //assimpMesh.setVertex(0, assimpVtx);
        //assimpMesh.setVertex(n - 1, assimpVtx);
        
        for (var posIdx = 0, fltIdx = 0; posIdx < numVertices; ++posIdx) {
            //assimpVtx.set(positions.array[fltIdx++], positions.array[fltIdx++], positions.array[fltIdx++]);
            //assimpMesh.setVertex(posIdx, assimpVtx);
            assimpMesh.setVertex(posIdx, positions.array[fltIdx++], positions.array[fltIdx++], positions.array[fltIdx++]);
        }
        
        //assimpVtx.delete();
    }

    function saveIndices(threeMesh, assimpMesh) {
        var indices = threeMesh.geometry.getIndex();
        var numIndices = indices.count;
        var numTris = numIndices / 3;
        assimpMesh.allocateTris(numTris);
        
        var t = assimpMesh.getFace(0);
        
        for (var triIdx = 0, idxIdx = 0; triIdx < numTris; ++triIdx) {
            assimpMesh.getFace(triIdx).setIndex(0, indices[idxIdx++]);
            assimpMesh.getFace(triIdx).setIndex(1, indices[idxIdx++]);
            assimpMesh.getFace(triIdx).setIndex(2, indices[idxIdx++]);
        }
    }

    function saveNormals(threeMesh, assimpMesh) {
        var normals = threeMesh.geometry.getAttribute('normal');
        var numVertices = normals.count;
        assimpMesh.allocateNormals(numVertices);
        //var assimpNrm = new Module.aiVector3D();
        
        for (var nrmIdx = 0, fltIdx = 0; nrmIdx < numVertices; ++nrmIdx) {
            //assimpNrm.set(normals.array[fltIdx++], normals.array[fltIdx++], normals.array[fltIdx++]);
            assimpMesh.setNormal(nrmIdx, normals.array[fltIdx++], normals.array[fltIdx++], normals.array[fltIdx++]);
        }
        //assimpNrm.delete();
    }

    function saveMesh(assimpScene, threeMesh) {
        var assimpMesh = new Module.aiMesh();
        assimpMesh.setPrimitiveTypes(Module.aiPrimitiveType.TRIANGLE.value);
        
        if(threeMesh.geometry.getAttribute('position') !== null) {
            savePositions(threeMesh, assimpMesh);
        }
        if(threeMesh.geometry.getAttribute('index') !== null) {
            saveIndices(threeMesh, assimpMesh);
        }
        if(threeMesh.geometry.getAttribute('normal') !== null) {
            saveNormals(threeMesh, assimpMesh);
        }
        if(threeMesh.geometry.getAttribute('color') !== null) {
            //saveVertexColors(threeMesh, assimpMesh);
        }
        if(threeMesh.geometry.getAttribute('uv') !== null) {
            //saveTextureCoords(threeMesh, assimpMesh);
        }
        if(threeMesh.geometry.getAttribute('uv2') !== null) {
            //saveTextureCoords(threeMesh, assimpMesh);
        }
        
    }

    function saveContents(threeScene) {
        var assimpScene = new Module.aiScene();
        threeScene.traverse(function(node) {

            if (node instanceof THREE.Mesh) {
                saveMesh(assimpScene, node);
            } else if (node instanceof THREE.Material) {
                //saveMaterial(assimpScene, node);
            } else if (node instanceof THREE.Texture) {
                //saveTexture(assimpScene, node);
            //} else if (node instanceof THREE.Animation) {
                //saveAnimation(assimpScene, node);
            } else if (node instanceof THREE.Camera) {
                //saveCamera(assimpScene, node);
            } else if (node instanceof THREE.Bone) {
                //saveBone(assimpScene, node);
            }
        });
        var exporter = new Module.Exporter();
        var str = exporter.exportToString(assimpScene, 'dae', null);
        exporter.delete();
        assimpScene.delete();
        
        return str;
    }

    return {
        loadContents: loadContents,
        saveContents: saveContents,
    };
})();