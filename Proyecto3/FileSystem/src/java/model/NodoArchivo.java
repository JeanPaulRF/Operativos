/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author david
 */
public class NodoArchivo extends Nodo {
    private String pathArchivo;
    private String contenido;
    private int cantidadbytes;
    private List<NodoUsuario> usuariosCompartido;
    
    public NodoArchivo(String nombre) {
        super(nombre, "Archivo");
        this.pathArchivo = nombre ;
        this.contenido = "";
        this.cantidadbytes = 0;
        this.usuariosCompartido = new ArrayList<>();
    }
    
    public void escribir(String palabras){
        this.contenido = this.contenido + palabras;
    }
    
    public void recetearContenido(){
        this.contenido = "";
    }
    
    public void calcularPesoBytes(){
        byte[] bytes = contenido.getBytes();
        this.cantidadbytes = bytes.length;
    }
    
    public int getBytes(){
        return this.cantidadbytes;
    }
    
    public String getContenido() {
        return this.contenido;
    }
    
    public String getPathArchivo() {
        return pathArchivo;
    }
    
    public void setPathArchivo(String pathArch){
        this.pathArchivo = pathArch;
    }
}
