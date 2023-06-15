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
        
        /*
        response.setContentType("text/html;charset=UTF-8");
        try ( PrintWriter out = response.getWriter()) {

            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet EliminarServlet</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Carpeta at " + nombreCarpeta + "</h1>");
            out.println("<h1>ruta at " + pathCopiarCarpeta + "</h1>");
            out.println("</body>");
            out.println("</html>");
        }
    */
        //define el nodo padre para volver
        //request.setAttribute("nodo", nodo);
        //request.getRequestDispatcher("explorador.jsp").forward(request, response);
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
