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
import model.NodoCarpeta;
import model.NodoRaiz;

/**
 *
 * @author jeanp
 */
public class CrearCarpetaServlet extends HttpServlet {




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
        String nombre = request.getParameter("nombreCrear");
        String path = request.getParameter("carpetaPath");

        NodoRaiz raiz = Globales.raiz;
        NodoCarpeta carpeta = raiz.buscarCarpeta(path);
        carpeta.crearNuevaCarpeta(nombre);

        // Agrega el nodo seleccionado como atributo en el objeto HttpServletRequest
        request.setAttribute("nodo", carpeta);   

        // Redirige nuevamente a explorador.jsp
        RequestDispatcher dispatcher = request.getRequestDispatcher("explorador.jsp");
        dispatcher.forward(request, response);
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
