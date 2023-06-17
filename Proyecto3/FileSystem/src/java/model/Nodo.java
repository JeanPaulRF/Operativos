/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author david
 */
import java.text.SimpleDateFormat;
import java.util.Date;

public class Nodo {
    public String nombre;
    public String tipoNodo;
    public Date fechaCreacion;
    public Date fechaMod;
    public String absolutePath;
    
    public Nodo(String nombre, String tiponodo) {
        this.nombre = nombre;
        this.tipoNodo = tiponodo;
        this.fechaCreacion = new Date(); // Establecer la fecha de creación al momento de crear el nodo
        this.fechaMod = new Date();
        this.absolutePath = "";
    }
    
    public String getNombre() {
        return nombre;
    }
    
    public String getTipo() {
        return tipoNodo;
    }
    
    public Date getFechaCreacion() {
        return fechaCreacion;
    }
    
    
    public void setFechaModificacion(Date fechaModif){
        this.fechaMod = fechaModif;
    }

    public String getAbsolutePath() {
        return absolutePath;
    }
    
    public String getFechaCreacionString() {
        SimpleDateFormat formato = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String fechaString = formato.format(this.fechaCreacion);
        return fechaString;
    }         

    
    public Date getFechaModificacion() {
        return fechaMod;
    }
    
    public String getFechaModificacionString() {
        SimpleDateFormat formato = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String fechaString = formato.format(this.fechaMod);
        return fechaString;
    }

    public void setFechaCreacion(Date fechaCreacion) {
        this.fechaCreacion = fechaCreacion;
    }

    public void setAbsolutePath(String absolutePath) {
        this.absolutePath = absolutePath;
    }
    
}