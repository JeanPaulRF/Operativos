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
import model.Globales;
import model.Nodo;
import model.NodoRaiz;

/**
 *
 * @author jeanp
 */
public class RegisterServlet extends HttpServlet {


    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String user = request.getParameter("user");
        String pass = request.getParameter("pass");
        
        NodoRaiz raiz = Globales.raiz;
        
        // Crear el usuario
        boolean result = raiz.crearUsuario(user, pass);
        
        if(result = true){
            // Obtener la URL de redirección con el parámetro user en la URL
            String redirectUrl = "index.jsp";

            // Redirigir a la página explorador.html
            response.sendRedirect(redirectUrl);
        }
        else{
            // Los datos ingresados son incorrectos, mostrar alerta
            String errorMessage = "El usuario ya existe. Ingrese uno nuevo";

            // Agregar el mensaje de alerta como atributo en el request
            request.setAttribute("errorMessage", errorMessage);
            
            request.getRequestDispatcher("register.jsp").forward(request, response);
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
