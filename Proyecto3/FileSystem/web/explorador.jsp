<%-- 
    Document   : explorador
    Created on : Jun 7, 2023, 9:17:19 PM
    Author     : jeanp
--%>

<%@ page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page import="model.*" %>
<!DOCTYPE html>
<html>

<head>
  <meta charset="UTF-8">
  <title>Drive</title>
  <style>
      
body {
  font-family: Arial, sans-serif;
  background-color: #222222; /* Fondo oscuro */
  color: #fff; /* Color de texto */
}

.container {
  max-width: 1200px;
  margin: 0 auto;
  padding: 20px;
}

.file-explorer {
  background-color: #222; /* Fondo oscuro */
  border-radius: 5px;
  box-shadow: 0px 2px 10px rgba(255, 255, 255, 0.1); /* Sombra clara */
  overflow: hidden;
}

.file-explorer-header {
  display: flex;
  background-color: #4d90fe;
  padding: 10px;
  border-bottom: 1px solid #757de8; /* Borde azul */
  color: #fff; /* Color de texto */
}



.file-explorer-header h2 {
  margin: 0;
  font-size: 20px;
}

.file-list {
  list-style-type: none;
  padding: 0;
  margin: 0;
}

.file-list-item {
  display: flex;
  align-items: center;
  padding: 10px;
  border-bottom: 1px solid #888; /* Borde oscuro */
}

.file-list-item:last-child {
  border-bottom: none;
}

.file-icon {
  width: 30px;
  height: 30px;
  margin-right: 10px;
}

.file-name {
  font-size: 16px;
  font-weight: bold;
}

.file-size {
  font-size: 14px;
  color: #999; /* Color de texto oscuro */
}

.file-actions {
  margin-left: auto;
}

.file-actions a {
  margin-left: 10px;
  text-decoration: none;
  color: #999; /* Color de enlace oscuro */
  font-size: 14px;
}

.file-actions a:hover {
  color: #ccc; /* Color de enlace oscuro al pasar el mouse */
}

.formulario-emergente {
  display: none;
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5); /* Fondo semitransparente */
}

.formulario-emergente-contenido {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  background-color: #222;
  padding: 20px;
  border-radius: 5px;
  text-align: center;
}

.formulario-emergente-contenido h3 {
  margin-top: 0;
}

.formulario-emergente-contenido input[type="text"],
.formulario-emergente-contenido button {
  margin-top: 10px;
}

  </style>
  
  <script>
      function mostrarFormularioCarpeta(path) {
        document.getElementById("formularioEmergenteCrearCarpeta").style.display = "block";
        document.getElementById("carpetaPath").value = path;
      }

      function ocultarFormularioCarpeta() {
        document.getElementById("formularioEmergenteCrearCarpeta").style.display = "none";
      }
      
      function mostrarFormularioArchivo(path) {
        document.getElementById("formularioEmergenteCrearArchivo").style.display = "block";
        document.getElementById("archivoPath").value = path;
      }

      function ocultarFormularioArchivo() {
        document.getElementById("formularioEmergenteCrearArchivo").style.display = "none";
      }
      
           
      function mostrarFormularioCompartirCarpeta(nombreCompartir) {
        document.getElementById("formularioEmergenteCompartirCarpeta").style.display = "block";
        document.getElementById("nombreCarpetaCompartir").value = nombreCompartir;
        document.getElementById("nombreCarpetaCompartirSpan").textContent = nombreCompartir;
      }

      function ocultarFormularioCompartirCarpeta() {
        document.getElementById("formularioEmergenteCompartirCarpeta").style.display = "none";
      }
      
      function mostrarFormularioCompartirArchivo(nombreCompartir) {
        document.getElementById("formularioEmergenteCompartirArchivo").style.display = "block";
        document.getElementById("nombreArchivoCompartir").value = nombreCompartir;
        document.getElementById("nombreArchivoCompartirSpan").textContent = nombreCompartir;
      }

      function ocultarFormularioCompartirArchivo() {
        document.getElementById("formularioEmergenteCompartirArchivo").style.display = "none";
      }
      
      function mostrarFormularioMoverCarpeta(nombreMover) {
        document.getElementById("formularioEmergenteMoverCarpeta").style.display = "block";
        document.getElementById("nombreCarpetaMover").value = nombreMover;
        document.getElementById("nombreCarpetaMoverSpan").textContent = nombreMover;
      }

      function ocultarFormularioMoverCarpeta() {
        document.getElementById("formularioEmergenteMoverCarpeta").style.display = "none";
      }
      
      function mostrarFormularioMoverArchivo(nombreMover) {
        document.getElementById("formularioEmergenteMoverArchivo").style.display = "block";
        document.getElementById("nombreArchivoMover").value = nombreMover;
        document.getElementById("nombreArchivoMoverSpan").textContent = nombreMover;
      }

      function ocultarFormularioMoverArchivo() {
        document.getElementById("formularioEmergenteMoverArchivo").style.display = "none";
      }
      
      function mostrarFormularioCopiarCarpeta(nombreCopiar) {
        document.getElementById("formularioEmergenteCopiarCarpeta").style.display = "block";
        document.getElementById("nombreCarpetaCopiar").value = nombreCopiar;
        document.getElementById("nombreCarpetaCopiarSpan").textContent = nombreCopiar;
      }

      function ocultarFormularioCopiarCarpeta() {
        document.getElementById("formularioEmergenteCopiarCarpeta").style.display = "none";
      }
      
      function mostrarFormularioCopiarArchivo(nombreCopiar) {
        document.getElementById("formularioEmergenteCopiarArchivo").style.display = "block";
        document.getElementById("nombreArchivoCopiar").value = nombreCopiar;
        document.getElementById("nombreArchivoCopiarSpan").textContent = nombreCopiar;
      }

      function ocultarFormularioCopiarArchivo() {
        document.getElementById("formularioEmergenteCopiarArchivo").style.display = "none";
      }
      
      function mostrarFormularioEliminarCarpeta(nombreEliminar) {
        document.getElementById("formularioEmergenteEliminarCarpeta").style.display = "block";
        document.getElementById("nombreCarpetaEliminar").value = nombreEliminar;
        document.getElementById("nombreCarpetaEliminarSpan").textContent = nombreEliminar;
      }

      function ocultarFormularioEliminarCarpeta() {
        document.getElementById("formularioEmergenteEliminarCarpeta").style.display = "none";
      }
      
      function mostrarFormularioEliminarArchivo(nombreEliminar) {
        document.getElementById("formularioEmergenteEliminarArchivo").style.display = "block";
        document.getElementById("nombreArchivoEliminar").value = nombreEliminar;
        document.getElementById("nombreArchivoEliminarSpan").textContent = nombreEliminar;
      }

      function ocultarFormularioEliminarArchivo() {
        document.getElementById("formularioEmergenteEliminarArchivo").style.display = "none";
      }
 
  </script>
</head>

<body>
    <div id="formularioEmergenteCrearCarpeta" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Nombre de la carpeta:</h3>
          <form action="crearCarpeta" method="post">
            <input type="hidden" id="carpetaPath" name="carpetaPath" value="">
            <input type="text" name="nombreCrear" required>
            <button type="submit">Crear</button>
            <button type="button" onclick="ocultarFormularioCarpeta()">Cancelar</button>
          </form>
        </div>
      </div>
    
    <div id="formularioEmergenteCrearArchivo" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Nombre del archivo: </h3>
          <form action="crearArchivo" method="post">
            <input type="hidden" id="archivoPath" name="archivoPath" value="">
            <input type="text" name="nombreCrear" required>
            <button type="submit">Crear</button>
            <button type="button" onclick="ocultarFormularioArchivo()">Cancelar</button>
          </form>
        </div>
      </div>

    <div id="formularioEmergenteCopiarCarpeta" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Copiar Carpeta <span id="nombreCarpetaCopiarSpan"></span></h3>
          <form action="copiar" method="post">
            <input type="hidden" id="nombreCarpetaCopiar" name="nombreCopiar" value="">
            <input type="hidden" id="tipo" name="tipo" value="1">
            <input type="text" name="pathCopiar" required>
            <button type="submit">Copiar</button>
            <button type="button" onclick="ocultarFormularioCopiarCarpeta()">Cancelar</button>
          </form>
        </div>
      </div>
    
    <div id="formularioEmergenteCopiarArchivo" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Copiar Archivo <span id="nombreArchivoCopiarSpan"></span></h3>
          <form action="copiar" method="post">
            <input type="hidden" id="nombreArchivoCopiar" name="nombreCopiar" value="">
            <input type="hidden" id="tipo" name="tipo" value="0">
            <input type="text" name="pathCopiar" required>
            <button type="submit">Copiar</button>
            <button type="button" onclick="ocultarFormularioCopiarArchivo()">Cancelar</button>
          </form>
        </div>
      </div>
    
    <div id="formularioEmergenteCompartirCarpeta" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Compartir Carpeta <span id="nombreCarpetaCompartirSpan"></span></h3>
          <form action="compartir" method="post">
            <input type="hidden" id="nombreCarpetaCompartir" name="nombreCompartir" value="">
            <input type="hidden" id="tipo" name="tipo" value="1">
            <input type="text" name="pathCompartir" required>
            <button type="submit">Compartir</button>
            <button type="button" onclick="ocultarFormularioCompartirCarpeta()">Cancelar</button>
          </form>
        </div>
      </div>
    
    <div id="formularioEmergenteCompartirArchivo" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Compartir Archivo <span id="nombreArchivoCompartirSpan"></span></h3>
          <form action="compartir" method="post">
            <input type="hidden" id="nombreArchivoCompartir" name="nombreCompartir" value="">
            <input type="hidden" id="tipo" name="tipo" value="0">
            <input type="text" name="pathCompartir" required>
            <button type="submit">Compartir</button>
            <button type="button" onclick="ocultarFormularioCompartirArchivo()">Cancelar</button>
          </form>
        </div>
      </div>
    
    <div id="formularioEmergenteMoverCarpeta" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Mover Carpeta <span id="nombreCarpetaMoverSpan"></span></h3>
          <form action="mover" method="post">
            <input type="hidden" id="nombreCarpetaMover" name="nombreMover" value="">
            <input type="hidden" id="tipo" name="tipo" value="1">
            <input type="text" name="pathMover" required>
            <button type="submit">Mover</button>
            <button type="button" onclick="ocultarFormularioMoverCarpeta()">Cancelar</button>
          </form>
        </div>
      </div>
    
    <div id="formularioEmergenteMoverArchivo" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Mover Archivo <span id="nombreArchivoMoverSpan"></span></h3>
          <form action="mover" method="post">
            <input type="hidden" id="nombreArchivoMover" name="nombreMover" value="">
            <input type="hidden" id="tipo" name="tipo" value="0">
            <input type="text" name="pathMover" required>
            <button type="submit">Mover</button>
            <button type="button" onclick="ocultarFormularioMoverArchivo()">Cancelar</button>
          </form>
        </div>
      </div>
    
    <div id="formularioEmergenteEliminarCarpeta" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Eliminar Carpeta <span id="nombreCarpetaEliminarSpan"></span></h3>
          <form action="eliminar" method="post">
            <input type="hidden" id="nombreCarpetaEliminar" name="nombreEliminar" value="">
            <input type="hidden" id="tipo" name="tipo" value="1">
            <input type="text" name="pathEliminar" required>
            <button type="submit">Eliminar</button>
            <button type="button" onclick="ocultarFormularioEliminarCarpeta()">Cancelar</button>
          </form>
        </div>
      </div>
    
    <div id="formularioEmergenteEliminarArchivo" class="formulario-emergente">
        <div class="formulario-emergente-contenido">
          <h3>Eliminar Archivo <span id="nombreArchivoEliminarSpan"></span></h3>
          <form action="eliminar" method="post">
            <input type="hidden" id="nombreArchivoEliminar" name="nombreEliminar" value="">
            <input type="hidden" id="tipo" name="tipo" value="0">
            <input type="text" name="pathEliminar" required>
            <button type="submit">Eliminar</button>
            <button type="button" onclick="ocultarFormularioEliminarArchivo()">Cancelar</button>
          </form>
        </div>
      </div>
    
  <div class="container">
    <div class="file-explorer">
      <div class="file-explorer-header">
        <h2>Drive: ${nodo.absolutePath}</h2>
        <a href="#" onclick="mostrarFormularioCarpeta('${nodo.getAbsolutePath()}')" class="file-actions">Crear Carpeta</a>
        <a href="#" onclick="mostrarFormularioArchivo('${nodo.getAbsolutePath()}')" class="file-actions">Crear Archivo</a>
      </div>
      
      <ul class="file-list">
        <c:forEach var="carpeta" items="${nodo.getCarpetas()}">
          <li class="file-list-item">
            <img class="file-icon" src="icons/carpeta.png" alt="Icono de carpeta">
            <div class="file-info">
              <span class="file-name">${carpeta.nombre}</span>
            </div>
            <div class="file-actions">
              <a href="abrirCarpeta?carpeta=${carpeta.absolutePath}">Abrir</a>
              <a href="#" onclick="mostrarFormularioCompartirCarpeta('${carpeta.getAbsolutePath()}')">Compartir</a>
              <a href="#" onclick="mostrarFormularioCopiarCarpeta('${carpeta.getAbsolutePath()}')">Copiar</a>
              <a href="#" onclick="mostrarFormularioMoverCarpeta('${carpeta.getAbsolutePath()}')">Mover</a>
              <a href="#" onclick="mostrarFormularioEliminarCarpeta('${carpeta.getAbsolutePath()}')">Eliminar</a>
            </div>
          </li>
        </c:forEach>
            
        <c:forEach var="archivo" items="${nodo.getArchivos()}">
          <li class="file-list-item">
          <img class="file-icon" src="icons/expediente.png" alt="Icono de archivo">
          <div class="file-info">
            <span class="file-name">${archivo.nombre}</span>
            <!-- <span class="file-size">1.2 MB</span> -->
          </div>
          <div class="file-actions">
              <a href="abrirArchivo?archivo=${archivo.absolutePath}">Abrir</a>
              <a href="#" onclick="mostrarFormularioCompartirArchivo('${archivo.getAbsolutePath()}')">Compartir</a>
              <a href="#" onclick="mostrarFormularioCopiarArchivo('${archivo.getAbsolutePath()}')">Copiar</a>
              <a href="#" onclick="mostrarFormularioMoverArchivo('${archivo.getAbsolutePath()}')">Mover</a>
              <a href="#" onclick="mostrarFormularioEliminarArchivo('${archivo.getAbsolutePath()}')">Eliminar</a>
              <a href="propiedades?archivo=${archivo.absolutePath}">Propiedades</a>
          </div>
        </li>
        </c:forEach>
          
        <!-- Agrega más elementos de la lista según sea necesario -->
      </ul>
      
      
    </div>
      <button onclick="history.back()">Atras</button>
  </div>
      
</body>

</html>