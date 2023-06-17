/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/Servlet.java to edit this template
 */

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.Globales;
import model.NodoArchivo;
import model.NodoRaiz;

/**
 *
 * @author jeanp
 */
public class PropiedadesServlet extends HttpServlet {


    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String archivoSeleccionado = request.getParameter("archivo");
        
        NodoRaiz raiz = Globales.raiz;

        // Obtén el nodo de carpeta correspondiente según el nombre seleccionado
        NodoArchivo nodoSeleccionado = raiz.buscarArchivo(archivoSeleccionado);
        
        //System.out.println(archivoSeleccionado);
        
        //System.out.println(nodoSeleccionado.nombre);
        //System.out.println(nodoSeleccionado.fechaCreacion);
        //System.out.println(nodoSeleccionado.fechaMod);
        //System.out.println(nodoSeleccionado.cantidadbytes);

        // Agrega el nodo seleccionado como atributo en el objeto HttpServletRequest
        request.setAttribute("nodo", nodoSeleccionado);

        // Redirige nuevamente a explorador.jsp
        request.getRequestDispatcher("propiedades.jsp").forward(request, response);
    }

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
