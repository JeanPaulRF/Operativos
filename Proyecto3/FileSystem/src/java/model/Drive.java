/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package model;

import java.util.ArrayList;

/**
 *
 * @author jeanp
 */
public class Drive {
    private static Drive instance;
    private ArrayList<NodoUsuario> usuarios;

    // Constructor privado para evitar la creación directa de instancias
    private Drive() {
        usuarios = new ArrayList<>();
    }

    public static Drive getInstance() {
        if (instance == null) {
            synchronized (Drive.class) {
                if (instance == null) {
                    instance = new Drive();
                }
            }
        }
        return instance;
    }

    public ArrayList<NodoUsuario> getUsuarios() {
        return usuarios;
    }

    public void setUsuarios(ArrayList<NodoUsuario> usuarios) {
        this.usuarios = usuarios;
    }
}

