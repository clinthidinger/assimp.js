/*jslint nomen: true, debug: true, evil: false, vars: true, white: true, browser: true, plusplus: true */
/*global ASSIMPJS, THREE */
var AssimpToThreeJS = (function() {

    'use strict';
    var ASSIMP = window.ASSIMP({noInitialRun: true});
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
            vertexClrAttr.setXYZ(vertIdx, clr.getX(), clr.getY(), clr.getZ());
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

    function loadMesh(mesh) {
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
        
        if (primType === ASSIMP.aiPrimitiveType.TRIANGLE.value) {
            loadTriIndices(mesh, geom);
        }
        else if (primType === ASSIMP.aiPrimitiveType.POLYGON.value) {
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
        return threeMesh;

        //parentNode.add(threeMesh);
    }

    function assimpMat4ToThreeMat4(assimpMat4) {
        var threeMat4 = new THREE.Matrix4()
        threeMat4.set(assimpMat4.getA1(), assimpMat4.getA2(), assimpMat4.getA3(), assimpMat4.getA4(),
                      assimpMat4.getB1(), assimpMat4.getB2(), assimpMat4.getB3(), assimpMat4.getB4(),
                      assimpMat4.getC1(), assimpMat4.getC2(), assimpMat4.getC3(), assimpMat4.getC4(),
                      assimpMat4.getD1(), assimpMat4.getD2(), assimpMat4.getD3(), assimpMat4.getD4());
        return threeMat4;
    }

    function threeMat4ToAssimpMat4(threeMat4) {
        var m0 = new ASSIMP.aiMatrix3x3();
        var m1 = new ASSIMP.aiMatrix4x4();
        var assimpMat4 = new ASSIMP.aiMatrix4x4(threeMat4.elements[0], threeMat4.elements[1], threeMat4.elements[2], threeMat4.elements[3],
                                                threeMat4.elements[4], threeMat4.elements[5], threeMat4.elements[6], threeMat4.elements[7],
                                                threeMat4.elements[8], threeMat4.elements[9], threeMat4.elements[10], threeMat4.elements[11],
                                                threeMat4.elements[12], threeMat4.elements[13], threeMat4.elements[14], threeMat4.elements[15]);
        return assimpMat4;
    }

    function loadNode(threeNode, assimpNode, meshArray) {
        var i = 0,
            numMeshes = assimpNode.getNumMeshes(),
            numChildren = assimpNode.getNumChildren(),
            meshIndex = 0,
            assimpChildNode = null,
            threeChildNode = null;
            //xformMat4 = null;

        threeNode.name = assimpNode.getName().str();
        threeNode.matrix = assimpMat4ToThreeMat4(assimpNode.getTransformation());
        
        for (i = 0; i < numMeshes; ++i) {
            meshIndex = assimpNode.getMeshIndex(i);
            threeNode.add(meshArray[meshIndex]);
        }
        for (i = 0; i < numChildren; ++i) {
            assimpChildNode = assimpNode.getChild(i);
            threeChildNode = new THREE.Object3D();
            threeNode.add(threeChildNode);
            loadNode(threeChildNode, assimpChildNode, meshArray);
        }
    }

    function loadContentsHack(contents) {
        var importer = new ASSIMP.Importer();
    var importer = new Module.Importer();
        var assimpScene = importer.readFileFromMemory(contents, ASSIMP.GetTargetRealtimeMaxQualityFlags());
        return assimpScene;
    }

    function loadContents(contents) {
        var i = 0;

        var threeScene = new THREE.Scene();
        var importer = new ASSIMP.Importer();
        //var importer = new Module.Importer();
        var assimpScene = importer.readFileFromMemory(contents, ASSIMP.GetTargetRealtimeMaxQualityFlags());

        var root = assimpScene.getRootNode();
        console.log(root.getName());
        var numChildren = root.getNumChildren();
        for(i = 0; i < numChildren; ++i)
        {
            console.log(root.getChild(i).getName());
            if(root.getChild(i).getNumMeshes() > 0) {
                console.log("Mesh count: " + root.getChild(i).getNumMeshes());
                console.log("Mesh index: " + root.getChild(i).getMeshIndex(0));
            }
        }

        //var exporter = new ASSIMP.Exporter();
        //exporter.exportToString(assimpScene, 'collada', null);
        //exporter.delete();
        var rootNode = assimpScene.getRootNode();

        var numMeshes = assimpScene.getNumMeshes();
        var numMaterials = assimpScene.getNumMaterials();
        var numLights = assimpScene.getNumLights();
        var numAnimations = assimpScene.getNumAnimations();
        var numTextures = assimpScene.getNumTextures();
        var numCameras = assimpScene.getNumCameras();

        for (i = 0; i < numMaterials; ++i) {
            var mat = assimpScene.getMaterial(i);
        }

        var meshArray = [];
        for (i = 0; i < numMeshes; ++i) {
            var mesh = assimpScene.getMesh(i);
            meshArray.push(loadMesh(mesh));
        }
        loadNode(threeScene, rootNode, meshArray);

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
        assimpMesh.setNumVertices(numVertices);
        //var assimpVtx = new ASSIMP.aiVector3D();
        
        
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
        var indices = threeMesh.geometry.getIndex(),
            numIndices = indices.count,
            numTris = numIndices / 3;

        assimpMesh.allocateTris(numTris);
        assimpMesh.setNumFaces(numTris);
        
        for (var triIdx = 0, idxIdx = 0; triIdx < numTris; ++triIdx) {
            var face = assimpMesh.getFace(triIdx);
            face.setNumIndices(3);
            face.allocateIndices(3);
            face.setIndex(0, indices.array[idxIdx++]);
            face.setIndex(1, indices.array[idxIdx++]);
            face.setIndex(2, indices.array[idxIdx++]);
            assimpMesh.setFace(triIdx, face);
        }
    }

    function saveNormals(threeMesh, assimpMesh) {
        var normals = threeMesh.geometry.getAttribute('normal'),
            numVertices = normals.count;

        assimpMesh.allocateNormals(numVertices);
        //var assimpNrm = new ASSIMP.aiVector3D();
        
        for (var nrmIdx = 0, fltIdx = 0; nrmIdx < numVertices; ++nrmIdx) {
            //assimpNrm.set(normals.array[fltIdx++], normals.array[fltIdx++], normals.array[fltIdx++]);
            assimpMesh.setNormal(nrmIdx, normals.array[fltIdx++], normals.array[fltIdx++], normals.array[fltIdx++]);
        }
        //assimpNrm.delete();
    }

    function saveVertexColors(threeMesh, assimpMesh, clrSetIndex) {
        var colors = threeMesh.geometry.getAttribute('color');//,
        var b1 = colors !== null;
        var b2 = colors ===  undefined;
            //numVertices = colors.count;

        assimpMesh.allocateVertexColors(clrSetIndex, numVertices);

        for (var clrIdx = 0, fltIdx = 0; clrIdx < numVertices; ++clrIdx) {
            assimpMesh.setVertexColor(uvSetIndex, uvIdx, colors.array[fltIdx++], color.array[fltIdx++], color.array[fltIdx++]);
        }
    }

    function saveTextureCoords(threeMesh, assimpMesh, uvSetIndex) {
        var uvs = threeMesh.geometry.getAttribute('uv');
        var numVertices = uvs.count;
        assimpMesh.allocateTextureCoords(uvSetIndex, numVertices);
        assimpMesh.setNumUVComponents(uvSetIndex, 2);

        for (var uvIdx = 0, fltIdx = 0; uvIdx < numVertices; ++uvIdx) {
            assimpMesh.setTextureCoord2(uvSetIndex, uvIdx, uvs.array[fltIdx++], uvs.array[fltIdx++]);
        }
    }

    function saveMesh(assimpScene, threeMesh, meshIndex) {
        var assimpMesh = new ASSIMP.aiMesh();
        assimpMesh.setPrimitiveTypes(ASSIMP.aiPrimitiveType.TRIANGLE.value);
        
        if(threeMesh.geometry.getAttribute('position') !== undefined) {
            savePositions(threeMesh, assimpMesh);
        }
        if(threeMesh.geometry.getIndex() !== null) {
            saveIndices(threeMesh, assimpMesh);
        }
        if(threeMesh.geometry.getAttribute('normal') !== undefined) {
            saveNormals(threeMesh, assimpMesh);
        }
        if(threeMesh.geometry.getAttribute('color') !== undefined) {
            assimpMesh.setNumColorChannels(1);
            saveVertexColors(threeMesh, assimpMesh, 0);
        }
        if(threeMesh.geometry.getAttribute('uv') !== undefined) {
            //assimpMesh.setNumUVChannels(1);
            saveTextureCoords(threeMesh, assimpMesh, 0);
        }
        if(threeMesh.geometry.getAttribute('uv2') !== undefined) {
            //simpMesh.setNumUVChannels(2);
            saveTextureCoords(threeMesh, assimpMesh, 1);
        }
        
        assimpScene.setMesh(meshIndex, assimpMesh);
        return assimpMesh;
        //assimpScene.
    }

    //function countMeshNodes(threeNode) {
     //   threeNode.traverse(function(node) {
     //       if (node instanceof THREE.Mesh) {
     //           ++numMeshes;
     //       }
     //   }
     //   for each child, call again
    //}

    /*
    function saveChildren(assimpScene, assimpNode, threeNode) {
        var i = 0,
            assimpChildNode = null,
            numChildren = threeNode.children.length;

        assimpChildNode.allocateChildren(numChildren);
        assimpNode.setNumChildren(numChildren);
        
        for (i = 0; i < numChildren; ++i) {
            assimpChildNode = new ASSIMP.aiNode();
            assimpNode.
            assimpNode.setChild(i, assimpChildNode);
            saveNode(assimpScene, assimpChildNode, threeNode.children[i]);
        }
    }
    */

    function saveNode(assimpScene, assimpNode, threeNode) {
        var i = 0,
            assimpChildNode = null,
            numChildren = threeNode.children.length;

        if (numChildren > 0) {
            assimpNode.allocateChildren(numChildren);
        }
        assimpNode.setNumChildren(numChildren);
        assimpNode.setName(threeNode.name);

        if (threeNode instanceof THREE.Mesh) {
            var sceneMeshIndex = assimpScene.getNumMeshes();
            var assimpMesh = saveMesh(assimpScene, threeNode, sceneMeshIndex);
            assimpScene.setMesh(sceneMeshIndex, assimpMesh);
            assimpScene.setNumMeshes(sceneMeshIndex + 1);
            assimpNode.setNumMeshes(1);
            assimpNode.setMeshIndex(0, sceneMeshIndex);
            console.log("Mesh Num Faces: " + assimpMesh.getNumFaces());
            console.log("Mesh Num Vertss: " + assimpMesh.getNumVertices());
            // Create assimp node.
            // Create assimp mesh.
            
            // Add mesh to scene.
            // Add mesh to node.
            // Add node to parent.
            //assimpNode
            // Set xform.
            //saveMesh(assimpScene, node);
            //saveChildren(assimpScene, assimpNode, threeNode);
        } else if (threeNode instanceof THREE.Material) {
            //saveMaterial(assimpScene, assimpScene, threeNode);
        } else if (threeNode instanceof THREE.Texture) {
            //saveTexture(assimpScene, node);
        //} else if (threeNode instanceof THREE.Animation) {
            //saveAnimation(assimpScene, node);
        } else if (threeNode instanceof THREE.Camera) {
            //saveCamera(assimpScene, node);
            //saveChildren(assimpScene, assimpNode, threeNode);
        } else if (threeNode instanceof THREE.Bone) {
            //saveBone(assimpScene, node);
            //saveChildren(assimpNode, threeNode);
        } else if (threeNode instanceof THREE.Group) {
            //saveChildren(assimpScene, assimpNode, threeNode);
        } else if (threeNode instanceof THREE.Scene) {
            //saveChildren(assimpScene, assimpNode, threeNode);
        } else if (threeNode instanceof THREE.Object3D) {
            //saveChildren(assimpScene, assimpNode, threeNode);
        }

        //var assimpMat4 = threeMat4ToAssimpMat4(threeNode.matrix);
        //assimpNode.setTransformation(assimpMat4);
        //assimpMat4.delete();
        assimpNode.getTransformation().set(threeNode.matrix.elements[0],
                                           threeNode.matrix.elements[1],
                                           threeNode.matrix.elements[2],
                                           threeNode.matrix.elements[3],
                                           threeNode.matrix.elements[4],
                                           threeNode.matrix.elements[5],
                                           threeNode.matrix.elements[6],
                                           threeNode.matrix.elements[7],
                                           threeNode.matrix.elements[8],
                                           threeNode.matrix.elements[9],
                                           threeNode.matrix.elements[10],
                                           threeNode.matrix.elements[11],
                                           threeNode.matrix.elements[12],
                                           threeNode.matrix.elements[13],
                                           threeNode.matrix.elements[14],
                                           threeNode.matrix.elements[15]);

        for (i = 0; i < numChildren; ++i) {
            assimpChildNode = new ASSIMP.aiNode();
            assimpChildNode.setParent(assimpNode);
            assimpNode.setChild(i, assimpChildNode);
            saveNode(assimpScene, assimpChildNode, threeNode.children[i]);
        }
    }

    function saveContentsHack(assimpScene) {
        var exporter = new ASSIMP.Exporter();
        var str = exporter.exportToString(assimpScene, 'collada', null);
        exporter.delete();
        return str;
    }

    function saveContents(threeScene) {
        var assimpScene = new ASSIMP.aiScene(),
            numMeshes = 0,
            numMaterials = 0,
            numTextures = 0,
            numLights = 0,
            numAnimations = 0,
            numCameras = 0,
            numBones = 0;

            //need to figure out nodes!!!!

        threeScene.traverse(function(node) {

            if (node instanceof THREE.Mesh) {
                ++numMeshes;
            } else if (node instanceof THREE.Material) {
                ++numMaterials;
            } else if (node instanceof THREE.Texture) {
                ++numTextures;
            //} else if (node instanceof THREE.Animation) {
            //    ++numAnimations;
            } else if (node instanceof THREE.Camera) {
                ++numCameras;
            } else if (node instanceof THREE.Bone) {
                ++numBones;
            }
        });

        var assimpRootNode = new ASSIMP.aiNode();
        assimpScene.setRootNode(assimpRootNode);
        
        // PROBLEM IS HERE!!!
        assimpScene.allocateMeshes(numMeshes);
        assimpScene.allocateMaterials(numMaterials);
        assimpScene.allocateTextures(numTextures);
        assimpScene.allocateCameras(numCameras);


        var n1 = assimpScene.getNumMeshes();
        assimpScene.setNumMeshes(0); // Reset count back to 0.
        assimpScene.setNumMaterials(numMaterials);
        assimpScene.setNumAnimations(numAnimations);
        assimpScene.setNumTextures(numTextures);
        assimpScene.setNumLights(numLights);
        assimpScene.setNumCameras(numCameras);

        //assimpScene.setMesh();
        //assimpScene.setMaterial();
        //asimpScene.setAnimation();
        ///assimpScene.setTexture();
        //assimpScene.setLight();

        saveNode(assimpScene, assimpRootNode, threeScene);
        /*
        var meshIndex = 0;
        threeScene.traverse(function(node) {

            if (node instanceof THREE.Mesh) {
                // Create assimp node.
                // Create assimp mesh.
                // Add mesh to scene.
                // Add mesh to node.
                // Add node to parent.
                saveMesh(assimpScene, node, meshIndex++);
            } else if (node instanceof THREE.Material) {
                saveMaterial(assimpScene, node);
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
        */
        var exporter = new ASSIMP.Exporter();
        var str = exporter.exportToString(assimpScene, 'collada', null);
        exporter.delete();
        assimpScene.delete();
        
        return str;
    }

    return {
        loadContents: loadContents,
        saveContents: saveContents,
        loadContentsHack: loadContentsHack,
        saveContentsHack: saveContentsHack,
    };
})();
