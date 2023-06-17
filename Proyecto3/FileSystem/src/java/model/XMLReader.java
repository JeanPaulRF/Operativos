package model;

import java.io.File;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class XMLReader {
    public static NodoRaiz leerDesdeXML(String nombreArchivo) {
        try {
            File archivoXML = new File(nombreArchivo);
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(archivoXML);
            document.getDocumentElement().normalize();

            Element elementoRaiz = document.getDocumentElement();
            NodoRaiz nodoRaiz = new NodoRaiz();

            NodeList nodosUsuario = elementoRaiz.getElementsByTagName("NodoUsuario");
            for (int i = 0; i < nodosUsuario.getLength(); i++) {
                Node nodoUsuario = nodosUsuario.item(i);
                if (nodoUsuario.getNodeType() == Node.ELEMENT_NODE) {
                    Element elementoUsuario = (Element) nodoUsuario;
                    NodoUsuario nodoUsuarioObj = crearNodoUsuarioDesdeElemento(elementoUsuario);
                    nodoRaiz.getUsuarios().add(nodoUsuarioObj);
                }
            }

            return nodoRaiz;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    private static NodoUsuario crearNodoUsuarioDesdeElemento(Element elementoUsuario) {
        String nombre = elementoUsuario.getAttribute("nombre");
        String fechaCreacion = elementoUsuario.getAttribute("fechaCreacion");
        String fechaMod = elementoUsuario.getAttribute("fechaMod");
        String absolutePath = elementoUsuario.getAttribute("absolutePath");
        String password = elementoUsuario.getAttribute("password");
        
        SimpleDateFormat formato = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        Date fechaCreDate = null;
        Date fechaModDate = null;
        
        try {
            fechaCreDate = formato.parse(fechaCreacion);
            fechaModDate = formato.parse(fechaMod);
        } catch (ParseException ex) {
            Logger.getLogger(XMLReader.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        NodoUsuario nodoUsuario = new NodoUsuario(nombre, password);
        nodoUsuario.setFechaCreacion(fechaCreDate);
        nodoUsuario.setFechaModificacion(fechaModDate);
        nodoUsuario.setAbsolutePath(absolutePath);
        
        
        NodeList nodosHijos = elementoUsuario.getChildNodes();
        for (int i = 0; i < nodosHijos.getLength(); i++) {
            Node nodoHijo = nodosHijos.item(i);
            if (nodoHijo.getNodeType() == Node.ELEMENT_NODE) {
                Element elementoHijo = (Element) nodoHijo;
                String nombreHijo = elementoHijo.getAttribute("nombre");
                String tipoNodoHijo = elementoHijo.getAttribute("tipoNodo");

                if (tipoNodoHijo.equals("Carpeta")) {
                    NodoCarpeta nodoCarpeta = crearNodoCarpetaDesdeElemento(elementoHijo);
                    nodoUsuario.getCarpetas().add(nodoCarpeta);
                } else if (tipoNodoHijo.equals("Archivo")) {
                    NodoArchivo nodoArchivo = crearNodoArchivoDesdeElemento(elementoHijo);
                    nodoUsuario.getArchivos().add(nodoArchivo);
                }
            }
        }

        return nodoUsuario;
    }

    private static NodoCarpeta crearNodoCarpetaDesdeElemento(Element elementoCarpeta) {
        String nombre = elementoCarpeta.getAttribute("nombre");
        String fechaCreacion = elementoCarpeta.getAttribute("fechaCreacion");
        String fechaMod = elementoCarpeta.getAttribute("fechaMod");
        String absolutePath = elementoCarpeta.getAttribute("absolutePath");
        String pathCarpeta = elementoCarpeta.getAttribute("pathCarpeta");
        
        SimpleDateFormat formato = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        Date fechaCreDate = null;
        Date fechaModDate = null;
        
        try {
            fechaCreDate = formato.parse(fechaCreacion);
            fechaModDate = formato.parse(fechaMod);
        } catch (ParseException ex) {
            Logger.getLogger(XMLReader.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        NodoCarpeta nodoCarpeta = new NodoCarpeta(nombre);
        nodoCarpeta.setFechaCreacion(fechaCreDate);
        nodoCarpeta.setFechaModificacion(fechaModDate);
        nodoCarpeta.setAbsolutePath(absolutePath);
        
        nodoCarpeta.setPathCarpeta(pathCarpeta);
        
        
        NodeList nodosHijos = elementoCarpeta.getChildNodes();
        for (int i = 0; i < nodosHijos.getLength(); i++) {
            Node nodoHijo = nodosHijos.item(i);
            if (nodoHijo.getNodeType() == Node.ELEMENT_NODE) {
                Element elementoHijo = (Element) nodoHijo;
                String tipoNodoHijo = elementoHijo.getAttribute("tipoNodo");

                if (tipoNodoHijo.equals("Carpeta")) {
                    NodoCarpeta subCarpeta = crearNodoCarpetaDesdeElemento(elementoHijo);
                    nodoCarpeta.getCarpetas().add(subCarpeta);
                } else if (tipoNodoHijo.equals("Archivo")) {
                    NodoArchivo archivo = crearNodoArchivoDesdeElemento(elementoHijo);
                    nodoCarpeta.getArchivos().add(archivo);
                }
            }
        }
        return nodoCarpeta;
    }

    private static NodoArchivo crearNodoArchivoDesdeElemento(Element elementoArchivo) {
        String nombre = elementoArchivo.getAttribute("nombre");
        String fechaCreacion = elementoArchivo.getAttribute("fechaCreacion");
        String fechaMod = elementoArchivo.getAttribute("fechaMod");
        String absolutePath = elementoArchivo.getAttribute("absolutePath");
        String pathArchivo = elementoArchivo.getAttribute("pathArchivo");
        
        SimpleDateFormat formato = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        Date fechaCreDate = null;
        Date fechaModDate = null;
        
        try {
            fechaCreDate = formato.parse(fechaCreacion);
            fechaModDate = formato.parse(fechaMod);
        } catch (ParseException ex) {
            Logger.getLogger(XMLReader.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        NodoArchivo nodoArchivo = new NodoArchivo(nombre);
        nodoArchivo.setFechaCreacion(fechaCreDate);
        nodoArchivo.setFechaModificacion(fechaModDate);
        nodoArchivo.setAbsolutePath(absolutePath);
        
        nodoArchivo.setPathArchivo(pathArchivo);
        return nodoArchivo;
    }
}