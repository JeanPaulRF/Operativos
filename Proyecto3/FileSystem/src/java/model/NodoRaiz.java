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
    private static NodoRaiz instance;
    private List<NodoUsuario> Usuarios;
    
    private NodoRaiz(){
        super("Origen", "Raiz");
        this.Usuarios = new ArrayList<>();
    }
    
    public static NodoRaiz getInstance() {
        if (instance == null) {
            synchronized (NodoRaiz.class) {
                if (instance == null) {
                    instance = new NodoRaiz();
                }
            }
        }
        return instance;
    }
    
    public void agregarUsuario(NodoUsuario newUser) {
        Usuarios.add(newUser);
    }
    
    public boolean existeUsuario(String nombreUser) {
        for (NodoUsuario usuario : Usuarios) {
            if (usuario.getNombre().equals(nombreUser)) {
                return true; // El nombre de usuario ya existe
            }
        }
        return false; // El nombre de usuario no existe
    }
    
    public void crearUsuario(String nombreUser, String contrasena) {
        // Verificar si el nombre del usuario ya existe
        if (existeUsuario(nombreUser)) {
            System.out.println("El nombre de usuario ya existe. No se puede crear.");
            return;
        }

        // Crear un nuevo NodoUsuario
        NodoUsuario nuevoUsuario = new NodoUsuario(nombreUser, contrasena);
        
        // Crear la carpeta inicial del nuevo usuario
        NodoCarpeta carpetaPrincipal = new NodoCarpeta("V:");
        nuevoUsuario.agregarCarpeta(carpetaPrincipal);

        // Agregar el nuevo usuario a la lista de usuarios
        agregarUsuario(nuevoUsuario);

        System.out.println("Usuario creado exitosamente.");
    }
    
    //funcion para buscar un archivo o carpeta por el path
    public NodoArchivo buscarArchivo(NodoUsuario user, String path){
        // se le inserta el usuario al que se le aplicara la busqueda
        // y luego el path con el cual empezara a buscar
        NodoArchivo archivoBuscado = user.buscarArchivo(path);
        
        return archivoBuscado;
    }
}
