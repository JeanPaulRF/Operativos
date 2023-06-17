<%-- 
    Document   : propiedades
    Created on : Jun 16, 2023, 2:21:44 PM
    Author     : jeanp
--%>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <title>Propiedades del Archivo</title>
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
</head>
<body>
    <div class="container">
        <div class="file-explorer">
            <div class="file-explorer-header">
                <h2>Propiedades del Archivo</h2>
            </div>
            <div class="file-list">
                <div class="file-list-item">
                    <span class="file-name">Nombre: </span>
                    <span>${nodo.getNombre()}</span>
                </div>
                <div class="file-list-item">
                    <span class="file-name">Extensión: </span>
                    <span>${nodo.getExtencion()}</span>
                </div>
                <div class="file-list-item">
                    <span class="file-name">Fecha de Creación: </span>
                    <span>${nodo.getFechaCreacion()}</span>
                </div>
                <div class="file-list-item">
                    <span class="file-name">Fecha de Modificación: </span>
                    <span>${nodo.getFechaMod()}</span>
                </div>
                <div class="file-list-item">
                    <span class="file-name">Tamaño: </span>
                    <span>${nodo.getBytes()} bytes</span>
                </div>
            </div>
                <button onclick="history.back()">Retroceder</button>
        </div>
        <div class="formulario-emergente">
            <div class="formulario-emergente-contenido">
                <h3>Formulario de Retroceso</h3>
                <button onclick="history.back()">Retroceder</button>
            </div>
        </div>
    </div>
</body>
</html>

