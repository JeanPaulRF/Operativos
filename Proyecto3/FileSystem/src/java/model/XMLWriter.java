package model;


import java.io.File;
import java.util.List;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;


public class XMLWriter {
    public static void guardarEnXML(NodoRaiz nodoRaiz, String nombreArchivo) {
        try {
            
            //Crear el builder
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.newDocument();

            //Acá va a empezar a bajar y escribir
            Element elementoRaiz = document.createElement("NodoRaiz");
            document.appendChild(elementoRaiz);
            agregarElementoUsuario(elementoRaiz, nodoRaiz);

            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");

            DOMSource source = new DOMSource(document);

            StreamResult result = new StreamResult(new File(nombreArchivo));

            transformer.transform(source, result);
            System.out.println("La información se ha guardado en el archivo XML correctamente.");
            
        } catch (ParserConfigurationException | TransformerException e) {
            e.printStackTrace();
        }
    }

    private static void agregarElementoUsuario(Element elementoRaiz, NodoRaiz nodoRaiz) {
        
        Document document = elementoRaiz.getOwnerDocument();
        List<NodoUsuario> usuarios = nodoRaiz.getUsuarios();
        
        for (NodoUsuario nodoHijo : usuarios){
            
            Element elementoUsuario = document.createElement("NodoUsuario");
            elementoUsuario.setAttribute("nombre", nodoHijo.getNombre());
            elementoUsuario.setAttribute("tipoNodo", nodoHijo.getTipo());
            elementoUsuario.setAttribute("fechaCreacion", nodoHijo.getFechaCreacionString());
            elementoUsuario.setAttribute("fechaMod", nodoHijo.getFechaModificacionString());
            elementoUsuario.setAttribute("absolutePath", nodoHijo.getAbsolutePath());
            elementoUsuario.setAttribute("password", nodoHijo.getPassword());
            
            agregarElementoCarpetaUsuario(elementoUsuario, nodoHijo);
            agregarElementoArchivoUsuario(elementoUsuario, nodoHijo);
            elementoRaiz.appendChild(elementoUsuario);          
        }
        
    }
    
    private static void agregarElementoCarpetaUsuario(Element elementoUsuario, NodoUsuario nodoPadre) {
        
        Document document = elementoUsuario.getOwnerDocument();
        List<NodoCarpeta> carpetas = nodoPadre.getCarpetas();
        
        for (NodoCarpeta nodoHijo : carpetas){
            
            Element elementoCarpeta = document.createElement("NodoCarpeta");
            elementoCarpeta.setAttribute("nombre", nodoHijo.getNombre());
            elementoCarpeta.setAttribute("tipoNodo", nodoHijo.getTipo());
            elementoCarpeta.setAttribute("fechaCreacion", nodoHijo.getFechaCreacionString());
            elementoCarpeta.setAttribute("fechaMod", nodoHijo.getFechaModificacionString());
            elementoCarpeta.setAttribute("absolutePath", nodoHijo.getAbsolutePath());
            elementoCarpeta.setAttribute("pathCarpeta", nodoHijo.getPathCarpeta());
            
            agregarElementoCarpeta(elementoCarpeta, nodoHijo);
            agregarElementoArchivo(elementoCarpeta, nodoHijo);
            elementoUsuario.appendChild(elementoCarpeta);          
        }
        
    }
    

    private static void agregarElementoArchivoUsuario(Element elementoUsuario, NodoUsuario nodoPadre) {
        
        Document document = elementoUsuario.getOwnerDocument();
        List<NodoArchivo> archivos = nodoPadre.getArchivos();
        
        for (NodoArchivo nodoHijo : archivos){
            
            Element elementoArchivo = document.createElement("NodoArchivo");
            elementoArchivo.setAttribute("nombre", nodoHijo.getNombre());
            elementoArchivo.setAttribute("tipoNodo", nodoHijo.getTipo());
            elementoArchivo.setAttribute("fechaCreacion", nodoHijo.getFechaCreacionString());
            elementoArchivo.setAttribute("fechaMod", nodoHijo.getFechaModificacionString());
            elementoArchivo.setAttribute("absolutePath", nodoHijo.getAbsolutePath());
            elementoArchivo.setAttribute("pathArchivo", nodoHijo.getPathArchivo());
            
            elementoArchivo.setAttribute("contenido", nodoHijo.getContenido());
            elementoArchivo.setAttribute("cantidadbytes", String.valueOf(nodoHijo.getBytes()));
            elementoArchivo.setAttribute("extencion", nodoHijo.getExtencion());
     
            elementoUsuario.appendChild(elementoArchivo);          
        }
    }
    
    private static void agregarElementoCarpeta(Element elementoPadre, NodoCarpeta nodoPadre) {
        
        Document document = elementoPadre.getOwnerDocument();
        List<NodoCarpeta> carpetas = nodoPadre.getCarpetas();
        
        for (NodoCarpeta nodoHijo : carpetas){
            
            Element elementoCarpeta = document.createElement("NodoCarpeta");
            elementoCarpeta.setAttribute("nombre", nodoHijo.getNombre());
            elementoCarpeta.setAttribute("tipoNodo", nodoHijo.getTipo());
            elementoCarpeta.setAttribute("fechaCreacion", nodoHijo.getFechaCreacionString());
            elementoCarpeta.setAttribute("fechaMod", nodoHijo.getFechaModificacionString());
            elementoCarpeta.setAttribute("absolutePath", nodoHijo.getAbsolutePath());
            elementoCarpeta.setAttribute("pathCarpeta", nodoHijo.getPathCarpeta());
            
            agregarElementoCarpeta(elementoCarpeta, nodoHijo);
            agregarElementoArchivo(elementoCarpeta, nodoHijo);
            elementoPadre.appendChild(elementoCarpeta);          
        }
    }
    

    private static void agregarElementoArchivo(Element elementoUsuario, NodoCarpeta nodoPadre) {
        
        Document document = elementoUsuario.getOwnerDocument();
        List<NodoArchivo> archivos = nodoPadre.getArchivos();
        
        for (NodoArchivo nodoHijo : archivos){
            
            Element elementoArchivo = document.createElement("NodoArchivo");
            elementoArchivo.setAttribute("nombre", nodoHijo.getNombre());
            elementoArchivo.setAttribute("tipoNodo", nodoHijo.getTipo());
            elementoArchivo.setAttribute("fechaCreacion", nodoHijo.getFechaCreacionString());
            elementoArchivo.setAttribute("fechaMod", nodoHijo.getFechaModificacionString());
            elementoArchivo.setAttribute("absolutePath", nodoHijo.getAbsolutePath());
            elementoArchivo.setAttribute("pathArchivo", nodoHijo.getPathArchivo());
            
            elementoArchivo.setAttribute("contenido", nodoHijo.getContenido());
            elementoArchivo.setAttribute("cantidadbytes", String.valueOf(nodoHijo.getBytes()));
            elementoArchivo.setAttribute("extencion", nodoHijo.getExtencion());           
            
            elementoUsuario.appendChild(elementoArchivo);          
        }
    }
    
}