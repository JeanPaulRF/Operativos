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


  </style>
</head>

<body>
  <div class="container">
    <div class="file-explorer">
      <div class="file-explorer-header">
        <h2>Drive: ${nodo.nombre}/</h2>
      </div>
      
      <ul class="file-list">
        <c:forEach var="carpeta" items="${nodo.getCarpetas()}">
          <li class="file-list-item">
            <img class="file-icon" src="icons/carpeta.png" alt="Icono de carpeta">
            <div class="file-info">
              <span class="file-name">${carpeta.nombre}</span>
            </div>
            <div class="file-actions">
              <a href="#">Abrir</a>
              <a href="#">Eliminar</a>
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
            <a href="editor.jsp">Abrir</a>
            <a href="#">Eliminar</a>
          </div>
        </li>
        </c:forEach>
          
        <!-- Agrega más elementos de la lista según sea necesario -->
      </ul>
    </div>
  </div>
</body>

</html>

