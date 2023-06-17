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
public class GuardarServlet extends HttpServlet {



    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String pathArchivo = request.getParameter("archivo");
        String contenido = request.getParameter("editor");
        
        NodoRaiz raiz = Globales.raiz;
        NodoArchivo archivo = raiz.buscarArchivo(pathArchivo);
        archivo.escribir(contenido);
        
        System.out.println(archivo.nombre + " guardado");
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
