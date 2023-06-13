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
import model.NodoUsuario;

/**
 *
 * @author jeanp
 */
public class ExploradorCarpetaServlet extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String carpetaSeleccionada = request.getParameter("carpeta");

        // Obtén el nodo de carpeta correspondiente según el nombre seleccionado
        NodoCarpeta nodoSeleccionado = obtenerNodoCarpeta(carpetaSeleccionada);

        // Agrega el nodo seleccionado como atributo en el objeto HttpServletRequest
        request.setAttribute("nodo", nodoSeleccionado);

        // Redirige nuevamente a explorador.jsp
        RequestDispatcher dispatcher = request.getRequestDispatcher("explorador.jsp");
        dispatcher.forward(request, response);
    }
    
    private NodoCarpeta obtenerNodoCarpeta(String nombreCarpeta) {
        // Realiza la lógica para encontrar el nodo de carpeta según el nombre seleccionado
        // Puedes recorrer tu estructura de carpetas y buscar por nombre o utilizar algún otro criterio

        // Ejemplo: Iterar a través de las carpetas en el nodo raíz y encontrar la coincidencia por nombre
        for (NodoCarpeta carpeta : nodoRaiz.getCarpetas()) {
            if (carpeta.getNombre().equals(nombreCarpeta)) {
                return carpeta;
            }
        }

        // Si no se encuentra la carpeta, puedes manejar el caso de error o devolver null
        return null;
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
