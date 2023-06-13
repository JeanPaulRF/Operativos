/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/Servlet.java to edit this template
 */

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.*;

/**
 *
 * @author jeanp
 */
public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String user = request.getParameter("user");
        String pass = request.getParameter("pass");

        // Validar las credenciales aquí
        boolean credentialsValid = true;
        
        // obtener el nodo
        NodoUsuario nodo = new NodoUsuario(user, pass);
        nodo.Carpetas.add(new NodoCarpeta("Desktop"));
        nodo.Carpetas.get(0).Carpetas.add(new NodoCarpeta("Docs"));
        nodo.Archivos.add(new NodoArchivo("word", "word"));

        if (credentialsValid) {
            // Obtener la URL de redirección con el parámetro user en la URL
            //String redirectUrl = request.getContextPath() + "/explorador.jsp";

            // Agregar el objeto UserObject como atributo en el request
            request.setAttribute("nodo", nodo);
            
            request.getRequestDispatcher("explorador.jsp").forward(request, response);

            // Redirigir a la página explorador.html
            //response.sendRedirect(redirectUrl);
        } else {
            // Los datos ingresados son incorrectos, mostrar alerta
            String errorMessage = "Credenciales incorrectas. Por favor, inténtalo de nuevo.";

            // Agregar el mensaje de alerta como atributo en el request
            request.setAttribute("errorMessage", errorMessage);

            // Obtener el objeto RequestDispatcher para redirigir al JSP de inicio de sesión
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.jsp");

            // Reenviar el request al JSP de inicio de sesión
            dispatcher.forward(request, response);
        }
    }




    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
