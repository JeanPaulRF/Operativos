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
import model.NodoArchivo;
import model.NodoCarpeta;
import model.NodoRaiz;
import model.NodoUsuario;

/**
 *
 * @author jeanp
 */
public class AbrirCarpetaServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String carpetaSeleccionada = request.getParameter("carpeta");
        
        System.out.println(carpetaSeleccionada);
        
        NodoRaiz raiz = NodoRaiz.getInstance();

        // Obtén el nodo de carpeta correspondiente según el nombre seleccionado
        NodoCarpeta nodoSeleccionado = raiz.buscarCarpeta(carpetaSeleccionada);

        // Agrega el nodo seleccionado como atributo en el objeto HttpServletRequest
        request.setAttribute("nodo", nodoSeleccionado);

        // Redirige nuevamente a explorador.jsp
        request.getRequestDispatcher("explorador.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        
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
