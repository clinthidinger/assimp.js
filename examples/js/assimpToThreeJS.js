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
        var numBones = mesh.getNumBones(),
            boneIdx,
            bone,
            numWeights,
            weights,
            wtIdx,
            weight,
            vtxId,
            weightValue,
            mtx;

        for (boneIdx = 0; boneIdx < numBones; ++boneIdx) {
            bone = mesh.getBone(boneIdx);
            numWeights = bone.getNumWeights();
            for (wtIdx = 0; wtIdx < numWeights; ++wtIdx) {
                weight = bone.getWeight(wtIdx);
                vtxId = weight.getVertexId();
                weightValue = weight.getWeight();
            }
            mtx = bone.getOffsetMatrix();
        }
    }

    function loadTexture(threeScene, texture) {

    }

    function loadMaterial(threeScene, material) {
        var numProperties = material.getNumProperties();
        var i = 0;
        for (i = 0; i < numProperties; i++) {
            var prop = material.getProperty(i);
            var key = prop.getKey();
            var type = prop.getType();
        }
    }

    function loadCamera(threeScene, camera) {
        var threeCam = new THREE.PerspectiveCamera(camera.getHorizontalFOV(),
                                                   camera.getAspect(),
                                                   camera.getClipPlaneNear(), 
                                                   camera.getClipPlaneFar()),
            pos = camera.getPosition(),
            lookAt = camera.getLookAt(),
            name = camera.getName();
        if (threeScene.getObjectByName(name, false) !== null) {
            return; // Make sure we don't re-add the default camera.
        }
        threeCam.name = name;
        threeCam.position.set(pos.getX(), pos.getY(), pos.getZ());
        threeCam.lookAt(new THREE.Vector3(lookAt.getX(), lookAt.getY(), lookAt.getZ()));
        var projMtx = new ASSIMP.aiMatrix4x4();
        camera.getCameraMatrix(projMtx)
        threeCam.projectionMatrix = assimpMat4ToThreeMat4(projMtx);
        //threeCam.projectionMatrix.set(projMtx.getA1(), projMtx.getB1(), projMtx.getC1(), projMtx.getD1(),
        //              projMtx.getA2(), projMtx.getB2(), projMtx.getC2(), projMtx.getD2(),
        //              projMtx.getA3(), projMtx.getB3(), projMtx.getC3(), projMtx.getD3(),
        //              projMtx.getA4(), projMtx.getB4(), projMtx.getC4(), projMtx.getD4());
        projMtx.delete();
        threeScene.add(threeCam);
        console.log('add cam');
    }

    function getLightTarget(assimpLight) {
        var pos = assimpLight.getPosition();
        var dir = assimpLight.getDirection();
        var threeTarget = new THREE.Vector3(pos.getX() + dir.getX(),
                                            pos.getY() + dir.getY(),
                                            pos.getZ() + dir.getZ());
        return threeTarget;
    }

    function loadLight(threeScene, assimpLight) {
        var lightType = assimpLight.getType(),
            threeLight = null,
            assimpDiffuseColor = assimpLight.getColorDiffuse(),
            assimpAmbientColor = assimpLight.getColorAmbient(),
            name = assimpLight.getName(),
            pos = assimpLight.getPosition(),
            threeDiffuseColor,
            threeAmbientColor,
            target;

        if (threeScene.getObjectByName(name, false) !== null) {
            return; // Make sure we don't re-add the default light.
        }

        if (lightType === ASSIMP.aiLightSourceType.AMBIENT) {
            threeAmbientColor = new THREE.Color(assimpAmbientColor.getR(),
                                                assimpAmbientColor.getB(),
                                                assimpAmbientColor.getG());
            threeLight = new THREE.AmbientLight(threeAmbientColor.getHex());
        }
        else if (lightType === ASSIMP.aiLightSourceType.POINT) {
            threeLight = new THREE.PointLight(color, intensity, distance);
        }
        else if (lightType === ASSIMP.aiLightSourceType.DIRECTIONAL) {
            threeDiffuseColor = new THREE.Color(assimpDiffuseColor.getR(),
                                                assimpDiffuseColor.getB(),
                                                assimpDiffuseColor.getG());
            threeLight = new THREE.DirectionalLight(threeDiffuseColor.getHex(), 1);
            //threeLight.target = getLightTarget(assimpLight); Needs to be an object, not a vec3!
        }
        else if (lightType === ASSIMP.aiLightSourceType.SPOT) {
            threeLight = new THREE.SpotLight();
            threeLight.angle = light.getAngleOuterCone();
            threeLight.penumbra = light.getAngleInnerCone();
            threeLight.decay = light.getAttenuationConstant();
            threeLight.color.setRGB(diffuseColor.getR(), diffuseColor.getG(), diffuseColor.getB());
            //threeLight.target = getLightTarget(assimpLight); Needs to be an object, not a vec3!
        }
        else if (lightType === ASSIMP.aiLightSourceType.UNDEFINED) {
            threeDiffuseColor = new THREE.Color(assimpDiffuseColor.getR(),
                                                assimpDiffuseColor.getB(),
                                                assimpDiffuseColor.getG());
            threeLight = new THREE.Light(threeDiffuseColor.getHex());
        }

        if (threeLight !== null) {
            threeLight.name = name;
            threeLight.position.set(pos.getX(), pos.getY(), pos.getZ());
            threeLight.intensity = 1.0;
            console.log('add light');
            threeScene.add(threeLight);
        }
    }


    function loadPositionKeys(animNode) {
        var posTrackName = animNode.getNodeName().str() + '_positionKeys',
            times = [],
            values = [];

        var numPositionKeys = animNode.getNumPositionKeys();
        for (var posKeyIdx = 0; posKeyIdx < numPositionKeys; ++posKeyIdx) {
            var posKey = animNode.getPositionKey(posKeyIdx);
            var t = posKey.getTime();
            var val = posKey.getValue();
            times.push(t);
            values.push(val.x);
            values.push(val.y);
            values.push(val.z);
        }
        var threePosTrack = new THREE.VectorKeyframeTrack(posTrackName, times, values);
        //threePosTrack.interpolation = ASSIMP.aiAnimBehaviour.;

        return threePosTrack;
    }

    function loadRotationKeys(animNode) {
        var rotTrackName = animNode.getNodeName().str() + '_rotationKeys',
            times = [],
            values = [];
            
        var numRotationKeys = animNode.getNumPositionKeys();
        for (var rotKeyIdx = 0; rotKeyIdx < numRotationKeys; ++rotKeyIdx) {
            var rotKey = animNode.getRotationKey(rotKeyIdx);
            var t = rotKey.getTime();
            var val = rotKey.getValue();
            times.push(t);
            values.push(val.x);
            values.push(val.y);
            values.push(val.z);
            values.push(val.w);
        }
        var threeRotTrack = new THREE.QuaternionKeyframeTrack(rotTrackName, times, values);

        return threeRotTrack;
    }

    function loadScalingKeys(animNode) {
        var scalTrackName = animNode.getNodeName().str() + '_scalingKeys',
            times = [],
            values = [];

        var numScalingKeys = animNode.getNumScalingKeys();
        for (var scalKeyIdx = 0; scalKeyIdx < numScalingKeys; ++scalKeyIdx) {
            var scalKey = animNode.getScalingKey(scalKeyIdx);
            var t = scalKey.getTime();
            var val = scalKey.getValue();
            times.push(t);
            values.push(val.x);
            values.push(val.y);
            values.push(val.z);
        }
        var threeScalTrack = new THREE.VectorKeyframeTrack(scalTrackName, times, values);

        return threeScalTrack;
    }

    function loadAnimation(threeScene, animation) {
        var name = animation.getName(),
            durtaion = animation.getDuration(),
            ticksPerSecond = animation.getTicksPerSecond(),
            numChannels = animation.getNumChannels(),
            numMeshChannels = animation.getNumMeshChannels();

            var tracks = [];
            for (var chanIdx = 0; chanIdx < numChannels; ++chanIdx ) {
                var animNode = animation.getChannel(chanIdx);
                var nodeName = animNode.getNodeName().str(); // name corresponds to bone or node name!!! add animations[] array to node
                var threeNode = threeScene.getObjectByName(nodeName, true);
                if (threeNode !== null) {
                    tracks.push(loadPositionKeys(animNode));
                    tracks.push(loadRotationKeys(animNode));
                    tracks.push(loadScalingKeys(animNode));
                    var threeAnimClip = new THREE.AnimationClip(name, duration, tracks); // Make a new clip for each node???
                    threeNode.animations = [];
                    threeNode.animations.push(threeAnimClip);
                    //animNode.getPreState();
                    //animNode.getPostState();
                }
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
        
        threeNode.name = assimpNode.getName();
        threeNode.applyMatrix(assimpMat4ToThreeMat4(assimpNode.getTransformation()));
        threeNode.updateMatrixWorld();
        
        for (i = 0; i < numMeshes; ++i) {
            meshIndex = assimpNode.getMeshIndex(i);
            threeNode.add(meshArray[meshIndex]);
        }
        for (i = 0; i < numChildren; ++i) {
            assimpChildNode = assimpNode.getChild(i);
            threeChildNode = new THREE.Object3D();
            threeNode.add(threeChildNode);
            //threeChildNode.updateMatrixWorld();
            loadNode(threeChildNode, assimpChildNode, meshArray);
        }
    }

    function loadContents(contents) {
        var i = 0;

        var threeScene = new THREE.Scene();
        var importer = new ASSIMP.Importer();
        var assimpScene = importer.readFileFromMemory(contents, ASSIMP.GetTargetRealtimeMaxQualityFlags());
        var rootNode = assimpScene.getRootNode();

        var numMeshes = assimpScene.getNumMeshes();
        var numMaterials = assimpScene.getNumMaterials();
        var numLights = assimpScene.getNumLights();
        var numAnimations = assimpScene.getNumAnimations();
        var numTextures = assimpScene.getNumTextures();
        var numCameras = assimpScene.getNumCameras();

        for (i = 0; i < numMaterials; ++i) {
            var mat = assimpScene.getMaterial(i);
            loadMaterial(threeScene, mat);
        }

        var meshArray = [];
        for (i = 0; i < numMeshes; ++i) {
            var mesh = assimpScene.getMesh(i);
            meshArray.push(loadMesh(mesh));
        }
        loadNode(threeScene, rootNode, meshArray);

        for (i = 0; i < numTextures; ++i) {
            var texture = assimpScene.getTexture(i);
            loadTexture(threeScene, texture);
        }
        for (i = 0; i < numLights; ++i) {
            var assimpLight = assimpScene.getLight(i);
            loadLight(threeScene, assimpLight);
        }
        for (i = 0; i < numAnimations; ++i) {
            var animation = assimpScene.getAnimation(i);
            //loadAnimation(threeScene, animation);
        }
        for (i = 0; i < numCameras; ++i) {
            var camera = assimpScene.getCamera(i);
            loadCamera(threeScene, camera);
        }

        importer.delete();
     
        return threeScene;
    }


    //////////=======================================================

    function savePositions(threeMesh, assimpMesh) {
        var positions = threeMesh.geometry.getAttribute('position');
        var numVertices = positions.count;
        assimpMesh.allocateVertices(numVertices);
        assimpMesh.setNumVertices(numVertices);
        
        for (var posIdx = 0, fltIdx = 0; posIdx < numVertices; ++posIdx) {
            assimpMesh.setVertex(posIdx, positions.array[fltIdx++], positions.array[fltIdx++], positions.array[fltIdx++]);
        }
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
    }

    function saveCamera(asssimpScene, threeCamera) {
        var assimpCam = new ASSIMP.aiCamera();
        assimpCam.setName(threeCamera.name);
        assimpCam.setPosition(threeCamera.position.x, threeCamera.position.y, threeCamera.position.z);
        //assimpCam.setLookAt(lookAt.x, lookAt.y, lookAt.z);
        
        if (threeCamera instanceof THREE.PerspectiveCamera) {
            assimpCam.setAspect(threeCamera.aspect);    
            assimpCam.setClipPlaneNear(threeCamera.near);
            assimpCam.setClipPlaneFar(threeCamera.far);
            assimpCam.setHorizontalFOV(threeCamera.fov);
        }
        else if (threeCamera instanceof THREE.OrthographicCamera) {
            assimpCam.setClipPlaneNear(threeCamera.near);
            assimpCam.setClipPlaneFar(threeCamera.far);
        }

        return assimpCam;
    }

    function getLightDirection(threeLight) {
        var pos = threeLight.position,
            target = threeLight.target.position,
            dir = new THREE.Vector3(target.x - pos.x, target.y - pos.y, target.z - pos.z);
        dir.normalize();

        return dir;
    }

    function saveLight(assimpScene, threeLight, light) {
        var assimpLight = new ASSIMP.aiLight(),
            pos,
            target,
            dir,
            intensity = threeLight.intensity;
        
        assimpLight.setName(threeLight.name);

        if (threeLight instanceof THREE.AmbientLight) {
            assimpLight.setType(ASSIMP.aiLightSourceType.AMBIENT);
            assimpLight.setColorAmbient(threeLight.color.r * intensity,
                                        threeLight.color.g * intensity,
                                        threeLight.color.b * intensity);
        } else if (threeLight instanceof THREE.PointLight) {
            assimpLight.setType(ASSIMP.aiLightSourceType.POINT);
            assimpLight.setColorDiffuse(threeLight.color.r * intensity,
                                        threeLight.color.g * intensity,
                                        threeLight.color.b * intensity);
            pos = threeLight.position;
            assimpLight.setPosition(pos.x, pos.y, pos.z);
        } else if (threeLight instanceof THREE.DirectionalLight) {
            assimpLight.setType(ASSIMP.aiLightSourceType.DIRECTIONAL);
            assimpLight.setColorDiffuse(threeLight.color.r * intensity,
                                        threeLight.color.g * intensity,
                                        threeLight.color.b * intensity);
            var dir = getLightDirection(threeLight);
            assimpLight.setDirection(dir.x, dir.y, dir.z);
        } else if (threeLight instanceof THREE.SpotLight) {
            assimpLight.setType(ASSIMP.aiLightSourceType.SPOT);
            assimpLight.setColorDiffuse(threeLight.color.r * intensity,
                                        threeLight.color.g * intensity,
                                        threeLight.color.b * intensity);
            
            assimpLight.setPosition(pos.x, pos.y, pos.z);
            var dir = getLightDirection(threeLight);
            assimpLight.setDirection(dir.x, dir.y, dir.z);
            assimpLight.setAngleOuterCone(threeLight.angle);
            assimpLight.setAngleInnerCone(threeLight.penumbra);
            assimpLight.setAttenuationConstant(threeLight.decay);
        } else {
            assimpLight.setType(ASSIMP.aiLightSourceType.UNDEFINED);
            assimpLight.setColorDiffuse(threeLight.color.r * intensity,
                                        threeLight.color.g * intensity,
                                        threeLight.color.b * intensity);
        }

        return assimpLight;
    }

    function saveNode(assimpScene, assimpNode, threeNode) {
        var i = 0,
            assimpChildNode = null,
            numChildren = threeNode.children.length,
            sceneIndex;

        console.log('save: ' + threeNode.name);

        if (numChildren > 0) {
            assimpNode.allocateChildren(numChildren);
        }
        assimpNode.setNumChildren(numChildren);
        assimpNode.setName(threeNode.name);

        if (threeNode instanceof THREE.Mesh) {
            sceneIndex = assimpScene.getNumMeshes();
            var assimpMesh = saveMesh(assimpScene, threeNode, sceneIndex);
            assimpScene.setMesh(sceneIndex, assimpMesh);
            assimpScene.setNumMeshes(sceneIndex + 1);
            assimpNode.setNumMeshes(1);
            assimpNode.setMeshIndex(0, sceneIndex);
        } else if (threeNode instanceof THREE.Material) {
            //saveMaterial(assimpScene, assimpScene, threeNode);
        } else if (threeNode instanceof THREE.Texture) {
            //saveTexture(assimpScene, threeNode);
        //} else if (threeNode instanceof THREE.Animation) {
            //saveAnimation(assimpScene, threeNode);
        } else if (threeNode instanceof THREE.Light) {
            sceneIndex = assimpScene.getNumLights();
            var assimpLight = saveLight(assimpScene, threeNode);
            //assimpScene.setLight(sceneIndex, assimpLight);
            assimpScene.setNumLights(sceneIndex + 1);
        } else if (threeNode instanceof THREE.Camera) {
            sceneIndex = assimpScene.getNumCameras();
            var assimpCam = saveCamera(assimpScene, threeNode);
            //assimpScene.setCamera(sceneIndex, assimpCam);
            assimpScene.setNumCameras(sceneIndex + 1);
        } else if (threeNode instanceof THREE.Bone) {
            //saveBone(assimpScene, threeNode);
        } else if (threeNode instanceof THREE.Group) {
        } else if (threeNode instanceof THREE.Scene) {
        } else if (threeNode instanceof THREE.Object3D) {
        }

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

    //function saveContentsHack(assimpScene) {
    //    var exporter = new ASSIMP.Exporter();
    //    var str = exporter.exportToString(assimpScene, 'collada', null);
    //    exporter.delete();
    //    return str;
    //}

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
            } else if (node instanceof THREE.Light) {
                ++numLights;
            } else if (node instanceof THREE.Camera) {
                ++numCameras;
            } else if (node instanceof THREE.Bone) {
                ++numBones;
            }
        });

        var assimpRootNode = new ASSIMP.aiNode();
        assimpScene.setRootNode(assimpRootNode);
        
        assimpScene.allocateMeshes(numMeshes);
        assimpScene.allocateMaterials(numMaterials);
        assimpScene.allocateTextures(numTextures);
        assimpScene.allocateCameras(numCameras);
        assimpScene.allocateLights(numLights);

        // Reset counts back to 0.  Will be set on load.
        assimpScene.setNumMeshes(0); 
        assimpScene.setNumMaterials(0);
        assimpScene.setNumAnimations(0);
        assimpScene.setNumTextures(0);
        assimpScene.setNumLights(0);
        assimpScene.setNumCameras(0);

        saveNode(assimpScene, assimpRootNode, threeScene);
       
        var exporter = new ASSIMP.Exporter();
        var str = exporter.exportToString(assimpScene, 'collada', null);
        exporter.delete();
        assimpScene.delete();
        
        return str;
    }

    return {
        loadContents: loadContents,
        saveContents: saveContents,
    };
})();
