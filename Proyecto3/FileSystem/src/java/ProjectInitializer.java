/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author jeanp
 */
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;
import model.*;

@WebListener
public class ProjectInitializer implements ServletContextListener {

    @Override
    public void contextInitialized(ServletContextEvent sce) {
        // Código de inicialización aquí
        // Esta función se ejecutará cuando el contexto del servlet se inicialice
        // Puedes realizar cualquier acción que necesites al inicio del proyecto
        // Por ejemplo, inicializar tus datos o configuraciones
        // Aquí puedes inicializar el ArrayList de Usuarios en la clase Drive
        System.out.println("Pagina iniciada");

        
        XMLReader lector = new XMLReader();        
        String path = "C:\\Users\\jeanp\\Mi unidad\\TEC\\Semestre VII\\Sistemas Operativos\\Operativos\\Proyecto3\\FileSystem\\src\\java\\model\\systemInformation.xml";
        NodoRaiz root = lector.leerDesdeXML(path);        
        
        Globales.raiz = root;
        
        // Añade los usuarios que necesites a la lista de usuarios
        //drive.getUsuarios().add(new NodoUsuario("admin", "admin"));
        //drive.getUsuarios().add(new NodoUsuario("123", "123"));
        // Establece la lista de usuarios en el objeto Drive
    }
 
    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        // Esta función se ejecutará cuando el contexto del servlet se destruya
        // Puedes realizar cualquier acción que necesites antes de finalizar el proyecto
        //NodoRaiz root = Globales.raiz;  
        
        //System.out.println("Pagina finalizada");
        
        //XMLWriter escritor = new XMLWriter(); 
        //C:\Users\jeanp\Mi unidad\TEC\Semestre VII\Sistemas Operativos\Operativos\Proyecto3\FileSystem\src\java\model
        //String path = "C:\\Users\\jeanp\\Mi unidad\\TEC\\Semestre VII\\Sistemas Operativos\\Operativos\\Proyecto3\\FileSystem\\src\\java\\model\\systemInformation.xml";
        //escritor.guardarEnXML(root, path); 
        
    }
}

