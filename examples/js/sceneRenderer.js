/* global THREE:false, Detector:false */
var SceneRenderer = (function () {
  'use strict'

  var isInit = false
  var camera = null
  var scene = null
  var renderer = null

  function checkWebGL () {
    if (!Detector.webgl) {
      alert('WebGL is not fully supported in this browser.')
      return false
    }
    return true
  }

  function init () {
    if (!checkWebGL()) {
      return;
    }
    camera = new THREE.PerspectiveCamera(70, window.innerWidth / window.innerHeight, 1, 1000)
    camera.position.z = 400
    renderer = new THREE.WebGLRenderer()
    renderer.setPixelRatio(window.devicePixelRatio)
    renderer.setSize(window.innerWidth, window.innerHeight)
    document.body.appendChild(renderer.domElement)
    isInit = true
  }

  function resize (width, height) {
    if (!isInit) {
      return
    }
    camera.aspect = width / height
    camera.updateProjectionMatrix()
    renderer.setSize(width, height)
  }

  //function animate () {
  //  requestAnimationFrame(animate)
  //  render()
  //}

  function render () {
    if ((scene === null) || !isInit) {
      return
    }
    scene.rotation.y += 0.005
    renderer.render(scene, camera)
  }

  function setCameraFromScene () {
    if ((scene === null) || !isInit) {
      return;
    }
    var bbox = new THREE.Box3()
    bbox.setFromObject(scene)
    var bsphere = bbox.getBoundingSphere()
    camera.position.x = bsphere.center.x
    camera.position.y = bsphere.center.y
    camera.position.z = -((bsphere.radius * 1.5) / Math.tan(THREE.Math.degToRad(camera.fov / 2.0)))
    camera.lookAt(bsphere.center)
  }

  function clearScene () {
    scene = null
  }

  function setScene (s) {
    scene = s
    setCameraFromScene()
  }

  function getScene () {
    return scene
  }

  return {
    init: init,
    render: render,
    clearScene: clearScene,
    getScene: getScene,
    setScene: setScene,
    resize: resize
  }
})()
