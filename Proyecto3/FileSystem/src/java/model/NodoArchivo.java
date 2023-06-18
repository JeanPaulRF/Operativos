/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

/**
 *
 * @author david
 */
public class NodoArchivo extends Nodo {
    private String contenido;
    private int cantidadbytes;
    private String extencion;
    private List<NodoUsuario> usuariosCompartido;
    
    public NodoArchivo(String nombre) {
        super(nombre, "Archivo");
        this.absolutePath = nombre ;
        this.extencion = "txt";
        this.contenido = "";
        this.cantidadbytes = 0;
        this.usuariosCompartido = new ArrayList<>();
    }
    
    public void escribir(String palabras){
        this.contenido = palabras;
    }
    
    public void recetearContenido(){
        this.contenido = "";
    }
    
    public void calcularPesoBytes(){
        byte[] bytes = contenido.getBytes();
        this.cantidadbytes = bytes.length;
    }
    
    public String getExtencion(){
        return this.extencion;
    }
    
    public void setExtencion(String ext){
        this.extencion = ext;
    }
    
    public int getBytes(){
        calcularPesoBytes();
        return this.cantidadbytes;
    }
    
    public String getContenido() {
        return this.contenido;
    }
    
    public String getPathArchivo() {
        return absolutePath;
    }
    
    public void setPathArchivo(String pathArch){
        this.absolutePath = pathArch;
    }
    
    public ArrayList<String> verPropiedades() {
        ArrayList<String> propiedades = new ArrayList<String>();
        propiedades.add("Nombre: " + this.getNombre());
        propiedades.add("Extension: .txt");
        propiedades.add("Fecha de creacion: " + this.getFechaCreacion().toString());
        propiedades.add("Fecha de modificacion: " + this.getFechaModificacion().toString());
        propiedades.add("Tamaño: " + this.getBytes());
    
        return propiedades;
    }
    
    public void corregirPath(String path){
        // Establecer el nuevo path
        String newpath = path + getNombre();
        
        // corregimos el actual
        setPathArchivo(newpath);
    }
    
    @Override
    public String getNombre() {
        return nombre;
    }

    public String getTipoNodo() {
        return tipoNodo;
    }

    @Override
    public Date getFechaCreacion() {
        return fechaCreacion;
    }

    public Date getFechaMod() {
        return fechaMod;
    }

    @Override
    public String getAbsolutePath() {
        return absolutePath;
    }
    
    
    public String getPathPadre(String path){
        String[] partes = path.split("/");
        
        String newpath = String.join("/", Arrays.copyOfRange(partes, 0, partes.length-1));
        
        return newpath;
    }

    public void setContenido(String contenido) {
        this.contenido = contenido;
    }

    public void setCantidadbytes(int cantidadbytes) {
        this.cantidadbytes = cantidadbytes;
    }
    
   
}
