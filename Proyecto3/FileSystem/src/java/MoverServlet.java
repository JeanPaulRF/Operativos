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
public class MoverServlet extends HttpServlet {

 
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String nombreCopiar = request.getParameter("nombreMover");
        String pathCopiarCarpeta = request.getParameter("pathMover");
        String tipo = request.getParameter("tipo");
       
        NodoRaiz raiz = Globales.raiz;
        
        if(tipo.equals("1")){
            NodoCarpeta carpeta = raiz.buscarCarpeta(nombreCopiar);
            NodoCarpeta padre = raiz.buscarCarpeta(carpeta.getPathPadre(nombreCopiar));
            
            NodoCarpeta borrada = padre.borrarCarpeta(carpeta.nombre);
            
            NodoCarpeta destino = raiz.buscarCarpeta(pathCopiarCarpeta);
            destino.agregarCarpeta(borrada);
            
            // Agrega el nodo seleccionado como atributo en el objeto HttpServletRequest
            request.setAttribute("nodo", padre);   

            // Redirige nuevamente a explorador.jsp
            RequestDispatcher dispatcher = request.getRequestDispatcher("explorador.jsp");
            dispatcher.forward(request, response);
        }
        else{
            NodoArchivo archivo = raiz.buscarArchivo(nombreCopiar);
            
            NodoCarpeta padre = raiz.buscarCarpeta(archivo.getPathPadre(nombreCopiar));
            
            NodoArchivo borrada = padre.borrarArchivo(archivo.nombre);
            
            NodoCarpeta destino = raiz.buscarCarpeta(pathCopiarCarpeta);
            destino.agregarArchivo(borrada);
            
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
