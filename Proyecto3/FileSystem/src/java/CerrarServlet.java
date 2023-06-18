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
import model.NodoRaiz;
import model.XMLWriter;

/**
 *
 * @author jeanp
 */
public class CerrarServlet extends HttpServlet {

    

    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        NodoRaiz root = Globales.raiz;  
        
        System.out.println("Pagina finalizada");
        
        XMLWriter escritor = new XMLWriter(); 
        //C:\Users\jeanp\Mi unidad\TEC\Semestre VII\Sistemas Operativos\Operativos\Proyecto3\FileSystem\src\java\model
        String path = "C:\\Users\\jeanp\\Mi unidad\\TEC\\Semestre VII\\Sistemas Operativos\\Operativos\\Proyecto3\\FileSystem\\src\\java\\model\\systemInformation.xml";
        escritor.guardarEnXML(root, path);
        
        // Obtener la URL de redirección con el parámetro user en la URL
        String redirectUrl = "index.jsp";

        // Redirigir a la página explorador.html
        response.sendRedirect(redirectUrl);
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
