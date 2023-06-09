<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">

<html>

<head>

  <meta charset="UTF-8">

  <title>Drive - Log-in</title>

  <style>
    @import url(http://fonts.googleapis.com/css?family=Roboto:400,100);
    
html {
  height: 100%;
  margin: 0;
}    

body {
  background-color: #222222;
  color: #fff;
  font-family: 'Roboto', sans-serif;
  height: 100%;
  margin: 0;
}

.container {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100%;
}

.login-card {
  padding: 40px;
  width: 274px;
  background-color: #222; /* Fondo oscuro */
  margin: 0 auto 10px;
  border-radius: 2px;
  box-shadow: 0px 2px 2px rgba(255, 255, 255, 0.3); /* Sombra clara */
  overflow: hidden;
  justify-content: center;
  align-items: center;
}

.login-card h1 {
  font-weight: 100;
  text-align: center;
  font-size: 2.3em;
}

.login-card input[type=submit] {
  width: 100%;
  display: block;
  margin-bottom: 10px;
  position: relative;
}

.login-card input[type=text],
input[type=password] {
  height: 44px;
  font-size: 16px;
  width: 100%;
  margin-bottom: 10px;
  -webkit-appearance: none;
  background: #000; /* Fondo oscuro */
  border: 1px solid #333; /* Borde oscuro */
  border-top: 1px solid #444; /* Borde superior oscuro */
  padding: 0 8px;
  box-sizing: border-box;
  -moz-box-sizing: border-box;
  color: #fff; /* Color de texto */
}

.login-card input[type=text]:hover,
input[type=password]:hover {
  border: 1px solid #555; /* Borde oscuro al pasar el mouse */
  border-top: 1px solid #666; /* Borde superior oscuro al pasar el mouse */
  -moz-box-shadow: inset 0 1px 2px rgba(255, 255, 255, 0.1);
  -webkit-box-shadow: inset 0 1px 2px rgba(255, 255, 255, 0.1);
  box-shadow: inset 0 1px 2px rgba(255, 255, 255, 0.1);
}

.login {
  text-align: center;
  font-size: 14px;
  font-family: 'Arial', sans-serif;
  font-weight: 700;
  height: 36px;
  padding: 0 8px;
  color: #fff; /* Color de texto */
}

.login-submit {
  border: 0;
  color: #fff;
  text-shadow: 0 1px rgba(0, 0, 0, 0.1);
  background-color: #4d90fe;
}

.login-submit:hover {
  border: 0;
  text-shadow: 0 1px rgba(0, 0, 0, 0.3);
  background-color: #357ae8;
}

.login-card a {
  text-decoration: none;
  color: #999; /* Color de enlace oscuro */
  font-weight: 400;
  text-align: center;
  display: inline-block;
  opacity: 0.6;
  transition: opacity ease 0.5s;
}

.login-card a:hover {
  opacity: 1;
}

.login-help {
  width: 100%;
  text-align: center;
  font-size: 12px;
}

    
  </style>

</head>

<body>
<div class="container">
  <div class="login-card">
    <h1>Drive Log-in</h1><br>
  <form action="explorador.jsp" method="get">
    <input type="text" name="user" placeholder="Username">
    <input type="password" name="pass" placeholder="Password">
    <input type="submit" name="login" class="login login-submit" value="login">
  </form>

    
  <div class="login-help">
    <a href="register.jsp">Register</a> 
  </div>
</div>

<!-- <div id="error"><img src="https://dl.dropboxusercontent.com/u/23299152/Delete-icon.png" /> Your caps-lock is on.</div> -->

  <script src='http://codepen.io/assets/libs/fullpage/jquery_and_jqueryui.js'></script>
</div>
</body>

</html>
