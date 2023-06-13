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

public class NodoRaiz extends Nodo{
    private List<NodoUsuario> Usuarios;
    
    public NodoRaiz(){
        super("Origen", "Raiz");
        this.Usuarios = new ArrayList<>();
    }
    
    public void agregarUsuario(NodoUsuario newUser) {
        Usuarios.add(newUser);
    }
}
