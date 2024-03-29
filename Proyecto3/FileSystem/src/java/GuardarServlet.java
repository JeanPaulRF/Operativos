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
import model.NodoArchivo;
import model.NodoCarpeta;
import model.NodoRaiz;

/**
 *
 * @author jeanp
 */
public class GuardarServlet extends HttpServlet {



    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String pathArchivo = request.getParameter("archivo");
        String contenido = request.getParameter("editor");
        
        NodoRaiz raiz = Globales.raiz;
        
        raiz.corregirPathRaiz();
        
        NodoArchivo archivo = raiz.buscarArchivo(pathArchivo);
        archivo.escribir(contenido);
        
        raiz.corregirPathRaiz();
        
        NodoCarpeta padre = raiz.buscarCarpeta(archivo.getPathPadre(pathArchivo));
            
        // Agrega el nodo seleccionado como atributo en el objeto HttpServletRequest
        request.setAttribute("nodo", padre);   

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
