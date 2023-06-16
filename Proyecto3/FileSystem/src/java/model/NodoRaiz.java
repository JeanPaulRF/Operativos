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
import java.util.Arrays;
import java.util.List;

public class NodoRaiz extends Nodo{
    private static NodoRaiz instance;
    public List<NodoUsuario> Usuarios;
    
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
        nuevoUsuario.crearCarpeta("V:");
        nuevoUsuario.crearCarpeta("Compartido");
        //nuevoUsuario.crearCarpeta();

        // Agregar el nuevo usuario a la lista de usuarios
        agregarUsuario(nuevoUsuario);

        System.out.println("Usuario creado exitosamente.");
    }
    
    //funcion para buscar un archivo o carpeta por el path
    // > quitar el nodoUsuario, agregar el path al usuario
    public NodoArchivo buscarArchivo(String path){
        
        // creamso al archivo de error
         NodoArchivo archivoError = new NodoArchivo("No existe, error 101");
         
         // Primero partimos el path
        String[] partes = path.split("/");
        
        // Buscamos al usuario que coincida con el partes[0]
        for(NodoUsuario user :Usuarios){
            if(user.getNombre().equals(partes[0])){
                // si encuentra una coincidencia, busca en el usuario
                String newpath = String.join("/", Arrays.copyOfRange(partes, 1, partes.length));
                return user.buscarArchivo(newpath);
            }
        }
        // no lo encontro
        System.out.println("Error en el path. El usuario no existe.");
        return archivoError;
    }
    
    public NodoCarpeta buscarCarpeta(String path){
        
        // creamos la carpeta de error
        NodoCarpeta carpetaError = new NodoCarpeta("No existe, error 102");
        
         // Primero partimos el path
        String[] partes = path.split("/");
        
        // Buscamos al usuario que coincida con el partes[0]
        for(NodoUsuario user :Usuarios){
            if(user.getNombre().equals(partes[0])){
                // si encuentra una coincidencia, busca en el usuario
                String newpath = String.join("/", Arrays.copyOfRange(partes, 1, partes.length));
                return user.buscarCarpeta(newpath);
            }
        }
        // no lo encontro
        System.out.println("Error en el path. El usuario no existe.");
        return carpetaError;
    }
}
