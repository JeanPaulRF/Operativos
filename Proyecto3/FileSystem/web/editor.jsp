<%-- 
    Document   : editor
    Created on : Jun 8, 2023, 6:46:16 PM
    Author     : jeanp
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
  <title>Editor de Texto</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #222222;
    }

    .container {
      max-width: 1200px;
      margin: 0 auto;
      padding: 20px;
    }

    .text-editor {
      background-color: #fff;
      border-radius: 5px;
      box-shadow: 0px 2px 10px rgba(0, 0, 0, 0.1);
      padding: 20px;
    }

    .text-editor textarea {
      width: 98%;
      height: 500px;
      padding: 10px;
      border: 1px solid #ccc;
      border-radius: 5px;
      resize: vertical;
      font-size: 14px;
      line-height: 1.5;
    }

    .text-editor button {
      padding: 10px 20px;
      background-color: #357ae8;
      border: none;
      border-radius: 5px;
      color: #fff;
      font-size: 14px;
      cursor: pointer;
    }
    
    .text-editor a {
      padding: 10px 20px;
      background-color: #A9A9A9;
      border: none;
      border-radius: 5px;
      color: #fff;
      font-size: 14px;
      cursor: pointer;
    }

    .text-editor button:hover {
      background-color: #1a237e;
    }
  </style>
</head>
<body>
  <div class="container">
    <div class="text-editor">
      <textarea id="editor"></textarea>
      <button onclick="saveFile()">Guardar</button>
      <a href="explorador.jsp">Salir</a>
    </div>
  </div>

  <script>
    <%--
    window.addEventListener('DOMContentLoaded', () => {
      // Obtener el elemento del textarea
      const textarea = document.getElementById('editor');
      
      // Realizar la carga del contenido del archivo de texto
      fetch('ruta/al/archivo.jsp')
        .then(response => response.text())
        .then(content => {
          // Asignar el contenido al valor del textarea
          textarea.value = content;
        })
        .catch(error => {
          console.error('Error al cargar el archivo:', error);
        });
    });
    --%>
      
    function saveFile() {
      var text = document.getElementById("editor").value;
      // Aquí puedes implementar la lógica para guardar el contenido del archivo.
      // Por ejemplo, podrías utilizar AJAX para enviar el contenido al servidor.
      alert("Archivo guardado.");
    }
  </script>
</body>
</html>
