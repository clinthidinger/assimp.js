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

    function loadIndices(mesh, geom) {

        var i,
            primType,
            numFaces,
            faces,
            triCount,
            face,
            numIndices,
            triIndicesAttr,
            faceTriIdx,
            faceIdx,
            indices = [],
            polyTriCount,
            tris,
            triIdx,
            tri;

        primType = mesh.getPrimitiveTypes();
        numFaces = mesh.getNumFaces();

        //faces = mesh.getFaces();
        if ((primType !== Module.aiPrimitiveType.TRIANGLE.value) && (primType !== Module.aiPrimitiveType.POLYGON.value)) {
            // unsupported type.
            console.log('Unsupported type: ' + primType);
            return;
        }
        // Compute tri count.
        /*
        if (primType === Module.aiPrimitiveType.TRIANGLE.value) {
            triCount = numFaces;
            triIndicesAttr = new THREE.BufferAttribute(new Uint16Array(triCount * 3), 1); // check if greater than max uint16
            var j = 0;
            for (faceIdx = 0; faceIdx < numFaces; ++faceIdx) {
                face = mesh.getFace(faceIdx);
                indices.length = 3;
                for (i = 0; i < 3; ++i) {
                    indices[i] = face.getIndex(i);
                }
                triIndicesAttr.array[j++] = indices[0];
                triIndicesAttr.array[j++] = indices[1];
                triIndicesAttr.array[j++] = indices[2];
            }
        }
        else*/ {
            triCount = getMeshTriCount(mesh);
            triIndicesAttr = new THREE.BufferAttribute(new Uint16Array(triCount * 3), 1); // check if greater than max uint16
            faceTriIdx = 0;
            var j = 0;
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
                    triIndicesAttr.array[j++] = tri[0];
                    triIndicesAttr.array[j++] = tri[1];
                    triIndicesAttr.array[j++] = tri[2];
                    //triIndicesAttr.setXYZ(faceTriIdx++, tri[0], tri[1], tri[2]);
                }
            }
        }

        geom.setIndex(triIndicesAttr);//geom.addAttribute('index', triIndicesAttr);
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
            numColorChannels,
            numUVChannels,
            threeMesh;

        geom = new THREE.BufferGeometry();
        name = mesh.getName();
        matIdx = mesh.getMaterialIndex();

        geom.addAttribute('name', name);
        geom.addAttribute('material_index', matIdx);

        if (!mesh.hasPositions() || !mesh.hasFaces()) {
            return geom;
        }

        loadPositions(mesh, geom);
        loadIndices(mesh, geom);

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

        //var format = "collada"; //! @see Exporter.cpp line 98 for supported formats.
        //var outStr = exporter.exportToString(scene, format, null);
        //var h = 0;
        return threeScene;
    }


    //////////=======================================================

    function savePositions(threeMesh, assimpMesh) {
        var numVertices = threeMesh.geometry.vertices.length;
        assimpMesh.setNumVertices(numVertices); // Need to allocate internally???
        var assimpVtx = new Module.aiVector3D();
        for (var i = 0; i < numVertices; ++i) {
            var threeVtx = threeMesh.geometry.vertices[i];
            assimpVtx.set(threeVtx.x, threeVtx.y, threeVtx.z);
            assimpMesh.setVertex(i, assimpVtx);
        }
    }

    function saveIndices(threeMesh, assimpMesh) {

    }

    function saveNormals(threeMesh, assimpMesh) {
        var numVertices = threeMesh.geometry.vertices.length;
        assimpMesh.setNumVertices(numVertices); // Need to allocate internally???
        var assimpNrm = new Module.aiVector3D();
        for (var i = 0; i < numVertices; ++i) {
            var threeNrm = threeMesh.geometry.normals[i];
            assimpNrm.set(threeNrm.x, threeNrm.y, threeNrm.z);
            assimpMesh.setNormal(i, assimpNrm);
        }
    }

    function saveMesh(threeMesh) {
        var assimpMesh = new Module.Mesh();
        savePositions(threeMesh, assimpMesh);
    }

    function saveContents(contents) {
        threeScene.traverse(function(node) {

            if (node instanceof THREE.Mesh) {
                saveMesh(node);
            } else if (node instanceof THREE.Material) {
                //saveMaterial(node);
            } else if (node instanceof THREE.Texture) {
                //saveTexture(node);
            } else if (node instanceof THREE.Animation) {
                //saveAnimation(node);
            } else if (node instanceof THREE.Camera) {
                //saveCamera(node);
            } else if (node instanceof THREE.Bone) {
                //saveCamera(node);
            }

            var exporter = new Module.Exporter();
            exporter.writeFileFromMemory();
        });
    }

    return {
        loadContents: loadContents,
        saveContents: saveContents,
    };
})();