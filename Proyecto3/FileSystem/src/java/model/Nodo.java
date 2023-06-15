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
    
    public Date getFechaModificacion() {
        return fechaMod;
    }
    
    public void setFechaModificacion(Date fechaModif){
        this.fechaMod = fechaModif;
    }

    public String getAbsolutePath() {
        return absolutePath;
    }
    
    
}