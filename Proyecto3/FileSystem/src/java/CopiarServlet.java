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
public class CopiarServlet extends HttpServlet {


    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String nombreCopiar = request.getParameter("nombreCopiar");
        String pathCopiarCarpeta = request.getParameter("pathCopiar");
        String tipo = request.getParameter("tipo");
       
        NodoRaiz raiz = Globales.raiz;
        
        if(tipo.equals("1")){
        
            NodoCarpeta carpeta = raiz.buscarCarpeta(nombreCopiar);
            NodoCarpeta destino = raiz.buscarCarpeta(pathCopiarCarpeta);
            destino.agregarCarpeta(carpeta);
            
            NodoCarpeta padre = raiz.buscarCarpeta(carpeta.getPathPadre(nombreCopiar));
            
            // Agrega el nodo seleccionado como atributo en el objeto HttpServletRequest
            request.setAttribute("nodo", padre);   

            // Redirige nuevamente a explorador.jsp
            RequestDispatcher dispatcher = request.getRequestDispatcher("explorador.jsp");
            dispatcher.forward(request, response);
        }
        else{
            NodoArchivo archivo = raiz.buscarArchivo(nombreCopiar);
            NodoCarpeta destino = raiz.buscarCarpeta(pathCopiarCarpeta);
            destino.agregarArchivo(archivo);
            
            NodoCarpeta padre = raiz.buscarCarpeta(archivo.getPathPadre(nombreCopiar));
            
            // Agrega el nodo seleccionado como atributo en el objeto HttpServletRequest
            request.setAttribute("nodo", padre);   

            // Redirige nuevamente a explorador.jsp
            RequestDispatcher dispatcher = request.getRequestDispatcher("explorador.jsp");
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
