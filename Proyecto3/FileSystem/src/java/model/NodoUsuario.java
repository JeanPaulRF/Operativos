
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
import java.util.ArrayList;
import java.util.List;

public class NodoUsuario extends Nodo{
    private List<NodoCarpeta> Carpetas;
    private String password;
    
    public NodoUsuario(String user, String clave){
        super(user, "Usuario");
        
        this.password = clave;
        this.Carpetas = new ArrayList<>();
        this.Carpetas.add(new NodoCarpeta("Compartido"));
    }
    
    public void agregarCarpeta(NodoCarpeta newCarpeta) {
        Carpetas.add(newCarpeta);
    }
    
    public String getPassword() {
        return password;
    }
    
    public void setPassword(String newPass){
        this.password = newPass;
    }
}
