#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h> 

typedef struct Admin{
    int estado;
    char nombre[50];
    char cedula[10];
    char direccion[50];
    char telefono[11];
    char correo[30];
    char login[100];
}Administrador;

typedef struct Med{
    int estado;
    char nombre[50];
    char cedula[9];
    char direccion[50];
    char telefono[11];
    char correo[30];
    char login[100];
}Medico;

typedef struct Pac{
    int estado;
    char medico[50];
    char nombre[50];
    char nss[12];
    char telefono[11];
    char correo[30];
    char login[100];
}Paciente;
  
typedef struct Cues{
    int estado;
    int puntuacion;
    int cuestionario;
    char paciente[50];
    char observaciones[1000]; 
    char fecha[40];
}Cuestionarios;

struct preguntasBeck{
    char pregunta[100];
};

struct respuestasBeck{
    char respuesta[150];
};

typedef struct Bec{
    char paciete[50];
    char fecha[40];
    struct preguntasBeck pregunta[21];    
    struct respuestasBeck respuesta[21];
}Beck;

struct preguntasMDI{
    char pregunta[100];
};

struct respuestasMDI{
    char respuesta[150];
};

typedef struct Md{
    char paciete[50];
    char fecha[40];
    struct preguntasMDI pregunta[13];    
    struct respuestasMDI respuesta[13];
}MDI;

struct preguntasZung{
    char pregunta[100];
};

struct respuestasZung{
    char respuesta[150];
};

typedef struct Zun{
    char paciete[50];
    char fecha[40];
    struct preguntasZung pregunta[19];    
    struct respuestasZung respuesta[19];
}Zung;

struct preguntasPh{
    char pregunta[150];
};

struct respuestasPh{
    char respuesta[150];
};

typedef struct Ph{
    char paciete[50];
    char fecha[40];
    struct preguntasPh pregunta[9];    
    struct respuestasPh respuesta[9];
}Phq9;

void continuar();
void registroAdministrador(int, Administrador *);
void loginAdministrador();
Administrador validarloginadmin(char[], char[]);
void menuAdministrador(Administrador *); 
void gestionarMedico();
void registrarMedico();
void actualizarInformacionMedico();
void cambiarEstatusMedico();
void eliminarMedico();
void transferirPacientes();
void generarInformesAdministrador();
void loginMedico();
Medico validarloginmed(char[], char[]);
void menuMedico(Medico *);
void modificarInformacionMedico(Medico **);
void gestionarPaciente(Medico *);
void registrarPaciente(Medico *);
void actualizarInformacionPaciente(Medico *);
void cambiarEstatusPaciente(Medico *);
void evaluarPaciente(Medico *);
void evaluacion(Paciente *);
void registrarConsulta(Paciente *);
void observaciones(Paciente *);
void asignarCuestionarios(Paciente *);
void verResultados(Paciente *);
void eliminarPaciente(Medico *);
void generarInformesMedico();
void loginPaciente();
Paciente validarloginpaci(char[], char[]);
void menuPaciente(Paciente *);
void responderCuestionarios(Paciente *);
void generarInformesPaciente(Paciente *);

int main(){
    Administrador admin;
    FILE *registroAdmin;
    int opcion, i, ciclo;
    char opc[100];
    ciclo = 1;
    while (ciclo == 1){
        registroAdmin = fopen("registroAdmin.bin", "rb");
        if(registroAdmin != NULL){
            do{
                opc[0] = '0';
                printf("\n                         Inicio de sesion\n");
                printf("\n(Ingrese el número de usuario que le corresponde)");
                printf("\n1) Administrador");
                printf("\n2) Médico");
                printf("\n3) Paciente");
                printf("\n4) Salir\n");
                scanf("%[^\n]%*c", opc);
                opcion = atoi(opc);
                if((opcion > 0 && opcion < 5)){
                    for (i = 0; i < (int)strlen(opc); i++){
                        if(!isdigit(opc[i])){
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            opcion = 0;
                            break;
                        }
                    }
                    switch (opcion){
                        case 1:
                            loginAdministrador();
                            break;
                        case 2:
                            loginMedico();
                            break;
                        case 3:
                            loginPaciente();
                            break;
                        case 4:
                            printf("Cerrando programa...");
                            opcion = 4;
                            break;
                    }
                }else{
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    fflush(stdin);
                    opcion = 0;
                }
            }while (opcion != 4 || opcion == 0);
            break;
        }else{
            fclose(registroAdmin);
            registroAdministrador(1, &admin);
        }
    }
}

void registroAdministrador(int CRUD, Administrador *admin){
    FILE *registroAdmin;
    if(CRUD == 1){
        registroAdmin = fopen("registroAdmin.bin", "wb");
        int opcion, longitud, i;
        char opc[100];
        char negativo[] = ("NO");
        printf("\n                         Registro del administrador\n");
        printf("\nIngrese los datos del administrador:\n");
        do{
            printf("Nombre completo: ");
            scanf("%[^\n]%*c", admin->nombre);  
            do{
                opc[0] = '0';
                printf("¿Continuar con el siguiente nombre [%s]?", admin->nombre);
                printf("\n1)Si          2)No          ");
                fflush(stdin);
                scanf("%[^\n]%*c", opc);
                opcion = atoi(opc);
                fflush(stdin);
                if (opcion != 1 && opcion != 2){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    fflush(stdin);
                }else{
                    for(i = 0; i < (int)strlen(opc); i++){
                        if(!isdigit(opc[i])){
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            opcion = 0;
                            break;
                        }
                    }
                }
            } while (opcion != 1 && opcion != 2);
        } while (opcion == 2);
        do{
            do{
                strcpy(admin->cedula, negativo);
                printf("Cédula profesional(8 caracteres): ");
                scanf("%[^\n]%*c", admin->cedula);
                fflush(stdin);
                longitud = strlen(admin->cedula);
                if (longitud != 8){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                }
            } while (longitud != 8);
            do{
                opc[0] = '0';
                printf("¿Continuar con la siguiente cédula [%s]?", admin->cedula);
                printf("\n1)Si          2)No          ");
                scanf("%[^\n]%*c", opc);
                opcion = atoi(opc);
                fflush(stdin);
                if (opcion != 1 && opcion != 2){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    fflush(stdin);
                }else{
                    for(i = 0; i <(int)strlen(opc); i++){
                        if(!isdigit(opc[i])){
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            opcion = 0;
                            break;
                        }
                    }
                }
            } while (opcion != 1 && opcion != 2);
        } while (opcion == 2);
        strcpy(admin->login, admin->cedula);
        printf("Dirección: ");
        fflush(stdin);
        scanf("%[^\n]%*c", admin->direccion);
        do{
            printf("Teléfono(10 dígitos): ");
            fflush(stdin);
            scanf("%[^\n]%*c", admin->telefono);
            if(strlen(admin->telefono) == 10){
                for (i = 0; i < (int)strlen(admin->telefono); i++){
                    if(!isdigit(admin->telefono[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                    opcion = 1;
                }
            }else{
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                opcion = 0;
            }
        }while(opcion != 1);
        printf("Correo electrónico: ");
        fflush(stdin);
        scanf("%[^\n]%*c", admin->correo);
        fwrite(admin, sizeof(Administrador), 1, registroAdmin);
        fclose(registroAdmin);
        return;
    }
    if(CRUD == 0){
        int opcion, longitud, i;
        char opc[3];
        char contra[100];
        printf("\n              Modificar información personal\n");
        printf("\nNombre: %s", admin->nombre);
        printf("\nCédula: %s", admin->cedula);
        printf("\nDirección: %s", admin->direccion);
        printf("\nTeléfono: %s", admin->telefono);
        printf("\nCorreo electrónico: %s", admin->correo);
        printf("\nContraseña: %s", admin->login);
        do{
            printf("\nSi desea cambiar su información personal presione 1, de lo contrario presione 2: ");
            scanf("%[^\n]%*c", opc);
            opcion = atoi(opc);
            if (opcion != 1 && opcion != 2){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente");
                fflush(stdin);
            }else{
                for(i = 0; i < (int)strlen(opc); i++){
                    if(!isdigit(opc[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente");
                        opcion = 0;
                        break;
                    }
                }
            }
        } while (opcion != 1 && opcion != 2);
        printf("Si desea omitir algún dato menos la contraseña solo presiona Enter\n");  
        if (opcion == 1){
            printf("\nIngrese el nuevo nombre completo: ");
            scanf("%[^\n]%*c", admin->nombre);
            fflush(stdin);
            do{
                do{
                    printf("Ingrese la nueva contraseña (Ingrese mínimo 5 caracteres): ");
                    scanf("%[^\n]%*c", admin->login);
                    fflush(stdin);
                    longitud = strlen(admin->login);
                    if (longitud < 5){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    }
                } while (longitud < 5);
                printf("Vuelva a ingresar la nueva contraseña: ");
                scanf("%[^\n]%*c", contra);
                fflush(stdin);
                if (strcmp(admin->login, contra) != 0){
                    printf("Las contraseñas no coinciden, intentalo nuevamente\n");
                }
            } while (strcmp(admin->login, contra) != 0);
            do{
                printf("Cédula profesional (8 caracteres): ");
                scanf("%[^\n]%*c", admin->cedula);
                fflush(stdin);
                longitud = strlen(admin->cedula);
                if (longitud != 8){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                }
            } while (longitud != 8);
            printf("Dirección: ");
            scanf("%[^\n]%*c", admin->direccion);
            fflush(stdin);
            do{
                printf("Teléfono(10 dígitos): ");
                scanf("%[^\n]%*c", admin->telefono);
                fflush(stdin);
                if(strlen(admin->telefono) == 10){
                    for (i = 0; i < (int)strlen(admin->telefono); i++){
                        if(!isdigit(admin->telefono[i])){
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            opcion = 0;
                            break;
                        }
                        opcion = 1;
                    }
                }else{
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                }
            }while(opcion != 1);
            printf("Correo electrónico: ");
            scanf("%[^\n]%*c", admin->correo);
            fflush(stdin);
            printf("Información actualizada con éxito\n");
            registroAdmin = fopen("registroAdmin.bin", "wb");
            fwrite(admin, sizeof(Administrador), 1, registroAdmin);
            fclose(registroAdmin);
        }
    }
}

void loginAdministrador(){
    printf("\nLogin Administrador\n");
    Administrador Admin;
    char nombreA[100];
    char nombreL[100];
    int intentos = 0;
    do{
        printf("Ingrese su nombre:");
        scanf("%[^\n]%*c", nombreA);
        printf("Ingrese su cédula:");
        scanf("%[^\n]%*c", nombreL);
        Admin = validarloginadmin(nombreA,nombreL);
        intentos++;
        if(intentos == 3){
            printf("\nHaz alcanzado el máximo de intentos\n");
            return;
        }
    }while(Admin.estado == 100);
    menuAdministrador(&Admin);
}

Administrador validarloginadmin(char nombre[100], char login[100]){
    FILE *archivo;
    Administrador Admin;
    int existe = 0;
    archivo = fopen("registroAdmin.bin", "rb");
    fread(&Admin, sizeof(Administrador),1,archivo);
    while(!feof(archivo)){
        if((strcmp(nombre, Admin.nombre) == 0)&&(strcmp(login, Admin.login) == 0)){
            existe = 1;
            break;
        }
        fread(&Admin, sizeof(Administrador),1,archivo);
    }
    fclose(archivo);
    if (existe ==1){
        return Admin;
    }else{
        Admin.estado = 100;
        return Admin;
    }
}

void menuAdministrador(Administrador *ptradmin){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          Bienvenido %s!\n", ptradmin->nombre);
        printf("\n¿Qué acción desea realizar? (Seleccione el número de la acción)");
        printf("\n1) Modificar información personal");
        printf("\n2) Gestionar Médico");
        printf("\n3) Generar informes");
        printf("\n4) Salir\n");
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if((opcion > 0 && opcion < 5)){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (opcion){
                case 1:
                    registroAdministrador(0, ptradmin);
                    break;
                case 2:
                    gestionarMedico();
                    break;
                case 3:
                    generarInformesAdministrador();
                    break;
                case 4:
                    printf("Cerrando sesión.\n");
                    break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 4 || opcion == 0);
}

void gestionarMedico(){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          Gestionar Médicos\n");
        printf("\n¿Qué acción desea realizar? (Seleccione el número de la acción)");
        printf("\n1) Registrar a un nuevo médico");
        printf("\n2) Actualizar información de un médico");
        printf("\n3) Habilitar o deshabilitar a un médico");
        printf("\n4) Eliminar a un médico");
        printf("\n5) Tranferir pacientes");
        printf("\n6) Salir\n");
        fflush(stdin);
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if(opcion > 0 && opcion < 7){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (opcion){
                case 1:
                    registrarMedico();
                    break;
                case 2:
                    actualizarInformacionMedico();
                    break;
                case 3:
                    cambiarEstatusMedico();
                    break;
                case 4:
                    eliminarMedico();
                    break;
                case 5:
                    transferirPacientes();
                    break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 6 || opcion == 0);
}

void registrarMedico(){
    printf("\n              Registrar a un nuevo médico\n");
    Medico med;
    FILE *registrarMedico;
    int opcion, i, longitud;
    char opc[100];
    char negativo[] = ("NO");
    registrarMedico = fopen("registroMedico.bin", "rb");
    if (registrarMedico == NULL){
        fclose(registrarMedico);
        registrarMedico = fopen("registroMedico.bin", "wb");
        fclose(registrarMedico);
    }
    fclose(registrarMedico);
    printf("\nIngrese los datos del médico:\n");
    med.estado = 1;
    do{
        printf("Nombre completo: ");
        scanf("%[^\n]%*c", med.nombre);  
        do{
            opc[0] = '0';
            printf("¿Continuar con el siguiente nombre [%s]?", med.nombre);
            printf("\n1)Si          2)No          ");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            opcion = atoi(opc);
            fflush(stdin);
            if (opcion != 1 && opcion != 2){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                fflush(stdin);
            }else{
                for(i = 0; i < (int)strlen(opc); i++){
                    if(!isdigit(opc[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                }
            }
        } while (opcion != 1 && opcion != 2);
    } while (opcion == 2);
    do{
        do{
            strcpy(med.cedula, negativo);
            printf("Cédula profesional(8 caracteres): ");
            scanf("%[^\n]%*c", med.cedula);
            fflush(stdin);
            longitud = strlen(med.cedula);
            if (longitud != 8){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            }
        } while (longitud != 8);
        do{
            opc[0] = '0';
            printf("¿Continuar con la siguiente cédula [%s]?", med.cedula);
            printf("\n1)Si          2)No          ");
            scanf("%[^\n]%*c", opc);
            opcion = atoi(opc);
            fflush(stdin);
            if (opcion != 1 && opcion != 2){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                fflush(stdin);
            }else{
                for(i = 0; i <(int)strlen(opc); i++){
                    if(!isdigit(opc[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                }
            }
        } while (opcion != 1 && opcion != 2);
    } while (opcion == 2);
    strcpy(med.login, med.cedula);
    printf("Dirección: ");
    fflush(stdin);
    scanf("%[^\n]%*c", med.direccion);
    do{
        printf("Teléfono(10 dígitos): ");
        fflush(stdin);
        scanf("%[^\n]%*c", med.telefono);
        if(strlen(med.telefono) == 10){
            for (i = 0; i < (int)strlen(med.telefono); i++){
                if(!isdigit(med.telefono[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
                opcion = 1;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            opcion = 0;
        }
    }while(opcion != 1);
    printf("Correo electrónico: ");
    fflush(stdin);
    scanf("%[^\n]%*c", med.correo);
    registrarMedico = fopen("registroMedico.bin", "ab");
    printf("Médico agregado con éxito!");
    fseek(registrarMedico, sizeof(Medico), SEEK_END);
    fwrite(&med, sizeof(Medico), 1, registrarMedico);
    fclose(registrarMedico);
}

void actualizarInformacionMedico(){
    Medico med, medicoBuscado;
    FILE *ptrmedicos = fopen("registroMedico.bin", "rb");
    int opcion, i;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrmedicos == NULL){
        printf("\nNo hay médicos registrados por el momento, regrese cuando haya registrado algún médico\n");
        fclose(ptrmedicos);
    }else{
        fclose(ptrmedicos);
        printf("\n                     Actualizar datos\n");
        printf("\n¿De qué médico desea actualizar los datos?");
        printf("\n(Escriba el nombre del médico)");
        do{
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            printf("\nLista de médicos:");
            fread(&med, sizeof(Medico), 1, ptrmedicos);
            do{
                printf("\n%s ", med.nombre);
                fread(&med, sizeof(Medico), 1, ptrmedicos);
            } while (feof(ptrmedicos) == 0);
            fclose(ptrmedicos);
            printf("\n(Si desea detener ésta acción escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrmedicos = fopen("registroMedico.bin", "r+b");
                fread(&med, sizeof(Medico), 1, ptrmedicos);
                do{
                    if (strcmp(opc, med.nombre) == 0){
                        strcpy(medicoBuscado.nombre, med.nombre);
                        printf("\nNombre: %s", med.nombre);
                        printf("\nCédula: %s", med.cedula);
                        printf("\nDirección: %s", med.direccion);
                        printf("\nTeléfono: %s", med.telefono);
                        printf("\nCorreo electrónico: %s", med.correo);
                        printf("\nContraseña: %s", med.login);
                        printf("\nSi desea omitir algún dato menos la contraseña solo presiona Enter\n");  
                            do{
                                respuesta[0] = '0';
                                printf("¿Estás seguro de actualizar la información de éste médico?");
                                printf("\n[%s]     1)Si    2)No     ", med.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);
                                if (opcion != 1 && opcion != 2){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    fflush(stdin);
                                }else{
                                    for (i = 0; i < (int)strlen(respuesta); i++){
                                        if (!isdigit(respuesta[i])){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);
                            if (opcion == 1){
                                int opcion, longitud, i;
                                char contra[100];
                                printf("\n              Modificar información personal\n");
                                printf("\nIngrese el nuevo nombre completo: ");
                                scanf("%[^\n]%*c", med.nombre);
                                fflush(stdin);
                                do{
                                    do{
                                        printf("Ingrese la nueva contraseña (Ingrese mínimo 5 caracteres): ");
                                        scanf("%[^\n]%*c", med.login);
                                        fflush(stdin);
                                        longitud = strlen(med.login);
                                        if (longitud < 5){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                        }
                                    } while (longitud < 5);
                                    printf("Vuelva a ingresar la nueva contraseña: ");
                                    scanf("%[^\n]%*c", contra);
                                    fflush(stdin);
                                    if (strcmp(med.login, contra) != 0){
                                        printf("Las contraseñas no coinciden, intentalo nuevamente\n");
                                    }
                                } while (strcmp(med.login, contra) != 0);
                                do{
                                    printf("Cédula profesional (8 caracteres): ");
                                    scanf("%[^\n]%*c", med.cedula);
                                    fflush(stdin);
                                    longitud = strlen(med.cedula);
                                    if (longitud != 8){
                                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    }
                                } while (longitud != 8);
                                printf("Dirección: ");
                                scanf("%[^\n]%*c", med.direccion);
                                fflush(stdin);
                                do{
                                    printf("Teléfono(10 dígitos): ");
                                    scanf("%[^\n]%*c", med.telefono);
                                    fflush(stdin);
                                    if(strlen(med.telefono) == 10){
                                        for (i = 0; i < (int)strlen(med.telefono); i++){
                                            if(!isdigit(med.telefono[i])){
                                                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                                opcion = 0;
                                                break;
                                            }
                                            opcion = 1;
                                        }
                                    }else{
                                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                        opcion = 0;
                                    }
                                }while(opcion != 1);
                                printf("Correo electrónico: ");
                                scanf("%[^\n]%*c", med.correo);
                                fflush(stdin);
                                printf("Información actualizada con éxito\n");
                                fseek(ptrmedicos,-(long)sizeof(Medico),SEEK_CUR);
                                fwrite(&med, sizeof(Medico), 1, ptrmedicos);
                                FILE *modName = fopen("registroPaciente.bin", "r+b");
                                Paciente auxiliar;
                                fread(&auxiliar, sizeof(Paciente), 1, modName);
                                do{
                                    if(strcmp(auxiliar.medico, medicoBuscado.nombre) == 0){
                                        FILE *lectura = fopen("registroPaciente.bin", "r+b");
                                        Paciente auxiliar2;
                                        strcpy(auxiliar.medico, med.nombre);
                                        fread(&auxiliar2, sizeof(Paciente), 1, lectura);
                                        do{
                                            if(strcmp(auxiliar2.medico, medicoBuscado.nombre) == 0){
                                                fseek(lectura,-(long)sizeof(Paciente),SEEK_CUR);
                                                fwrite(&auxiliar, sizeof(Paciente), 1, lectura);
                                                break;
                                            }
                                            fread(&auxiliar2, sizeof(Paciente), 1, lectura);
                                        } while (feof(lectura) == 0);
                                        fclose(lectura);
                                    }
                                    fread(&auxiliar, sizeof(Paciente), 1, modName);
                                } while (feof(modName) == 0);
                                fclose(modName);
                            }   
                        break;
                    }else{
                        fread(&med, sizeof(Medico), 1, ptrmedicos);
                        opcion = 0;
                    }
                } while (feof(ptrmedicos) == 0);
                if (opcion == 0){
                    printf("Médico no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrmedicos);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menú Gestionar médicos\n");
    }
}

void cambiarEstatusMedico(){
    Medico med;
    FILE *ptrmedicos = fopen("registroMedico.bin", "rb");
    int opcion, i;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrmedicos == NULL){
        printf("\nNo hay médicos registrados por el momento, regrese cuando haya registrado algún médico\n");
        fclose(ptrmedicos);
    }else{
        fclose(ptrmedicos);
        printf("\n                     Habilitar o deshabilitar\n");
        printf("\n¿Qué médico desea habilitar o deshabilitar?");
        printf("\n(Escriba el nombre del médico)");
        do{
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            printf("\nLista de médicos:");
            fread(&med, sizeof(Medico), 1, ptrmedicos);
            do{
                printf("\n%s ", med.nombre);
                if (med.estado == 1){
                    printf("(Habilitado)");
                }
                if (med.estado == 0){
                    printf("(Deshabilitado)");
                }
                fread(&med, sizeof(Medico), 1, ptrmedicos);
            } while (feof(ptrmedicos) == 0);
            fclose(ptrmedicos);
            printf("\n(Si desea detener esta acción escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrmedicos = fopen("registroMedico.bin", "r+b");
                fread(&med, sizeof(Medico), 1, ptrmedicos);
                do{
                    if (strcmp(opc, med.nombre) == 0){
                        if (med.estado == 1){
                            do{
                                respuesta[0] = '0';
                                printf("¿Estás seguro de inhabilitar a este médico?");
                                printf("\n[%s]     1)Si    2)No     ", med.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);
                                if (opcion != 1 && opcion != 2){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    fflush(stdin);
                                }else{
                                    for (i = 0; i < (int)strlen(respuesta); i++){
                                        if (!isdigit(respuesta[i])){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);
                            if (opcion == 1){
                                med.estado = 0;
                                fseek(ptrmedicos,-(long)sizeof(Medico),SEEK_CUR);
                                fwrite(&med, sizeof(Medico), 1, ptrmedicos);
                                printf("¡Deshabilitado!\n");
                            }
                        }else{
                            if (med.estado == 0){
                                do{
                                    respuesta[0] = '0';
                                    printf("¿Estás seguro de habilitar a este médico?");
                                    printf("\n[%s]     1)Si    2)No     ", med.nombre);
                                    fflush(stdin);
                                    scanf("%[^\n]%*c", respuesta);
                                    opcion = atoi(respuesta);
                                    fflush(stdin);
                                    if (opcion != 1 && opcion != 2){
                                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                        fflush(stdin);
                                    }else{
                                        for (i = 0; i < (int)strlen(respuesta); i++){
                                            if (!isdigit(respuesta[i])){
                                                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                                opcion = 0;
                                                break;
                                            }
                                        }
                                    }
                                } while (opcion != 1 && opcion != 2);
                                if (opcion == 1){
                                    med.estado = 1;
                                    fseek(ptrmedicos,-(long)sizeof(Medico),SEEK_CUR);
                                    fwrite(&med, sizeof(Medico), 1, ptrmedicos);
                                    printf("¡Habilitado!\n");
                                }
                            }
                        }
                        break;
                    }else{
                        fread(&med, sizeof(Medico), 1, ptrmedicos);
                        opcion = 0;
                    }
                } while (feof(ptrmedicos) == 0);
                if (opcion == 0){
                    printf("Médico no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrmedicos);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menú Gestionar médicos\n");
    }
}

void eliminarMedico(){
    Medico medicos, copiaMedicos;
    FILE *ptrmedicos = fopen("registroMedico.bin", "rb");
    int opcion, i, check, contador;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrmedicos == NULL){
        printf("\nNo hay médicos registrados por el momento, regrese cuando haya registrado a algún médico\n");
        fclose(ptrmedicos);
    }else{
        fclose(ptrmedicos);
        printf("\n                     Eliminar médico\n");
        printf("\nPara eliminar un médico primero debe deshabilitarlo, además no debe contar con pacientes registrados");
        printf("\n¿Qué médico desea eliminar?");
        printf("\n(Escriba el nombre del médico)");
        do{
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            printf("\nLista de médicos deshabilitados:");
            fread(&medicos, sizeof(Medico), 1, ptrmedicos);
            do{
                if (medicos.estado == 0){
                    printf("\n%s ", medicos.nombre);
                }
                fread(&medicos, sizeof(Medico), 1, ptrmedicos);
            } while (feof(ptrmedicos) == 0);
            fclose(ptrmedicos);
            printf("\n(Si desea detener esta acción escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrmedicos = fopen("registroMedico.bin", "r+b");
                fread(&copiaMedicos, sizeof(Medico), 1, ptrmedicos);
                contador = 1;
                do{
                    if ((strcmp(opc, copiaMedicos.nombre) == 0) && copiaMedicos.estado == 0){
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        check = 1;
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        //Verificar que el medico no tenga pacientes registrados
                        if (check == 1){
                            do{
                                respuesta[0] = '0';
                                printf("¿Estás seguro de eliminar a éste médico?");
                                printf("\n[%s]     1)Si    2)No     ", copiaMedicos.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);
                                if (opcion != 1 && opcion != 2){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    fflush(stdin);
                                }else{
                                    for (i = 0; i < (int)strlen(respuesta); i++){
                                        if (!isdigit(respuesta[i])){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);
                            if (opcion == 1){
                                FILE *copiaptrMedicos = fopen("registroMedicoCopia.bin", "wb");
                                fseek(ptrmedicos, contador * -(long)sizeof(Medico), SEEK_CUR);
                                fread(&medicos, sizeof(Medico), 1, ptrmedicos);
                                do{
                                    if(strcmp(copiaMedicos.nombre, medicos.nombre) != 0){
                                        fwrite(&medicos, sizeof(Medico), 1, copiaptrMedicos);
                                    }
                                    fread(&medicos, sizeof(Medico), 1, ptrmedicos);
                                } while (feof(ptrmedicos) == 0);
                                fclose(ptrmedicos);
                                fclose(copiaptrMedicos);
                                remove("registroMedico.bin");
                                rename("registroMedicoCopia.bin", "registroMedico.bin");
                            }
                        }else{
                            printf("El médico ingresado tiene pacientes registrados, por lo tanto no fue posible eliminarlo");
                        }
                        break;
                    }else{
                        fread(&copiaMedicos, sizeof(Medico), 1, ptrmedicos);
                        opcion = 0;
                        contador++;
                    }
                } while (feof(ptrmedicos) == 0);
                if (opcion == 0){
                    printf("Médico no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrmedicos);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menú| Gestionar médicos\n");
    }
}

//Coregir
//Coregir
//Coregir
//Coregir
//Coregir
//Coregir
//Coregir
//Coregir
//Coregir
//Coregir

void transferirPacientes() {
    Paciente pac, pacienteBuscado;
    FILE *ptrpacientes = fopen("registroPaciente.bin", "rb");
    Medico medicos;
    FILE *ptrmedicos = fopen("registroMedico.bin", "rb");
    int opcion, i, check, contador;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    char nombreAux[50];

    if (ptrmedicos == NULL) {
        printf("\nNo hay medicos registrados por el momento, regrese cuando alla registrado a algun medico\n");
        fclose(ptrmedicos);
    } else {
        fclose(ptrmedicos);
        printf("\n                     Transferir los pacientes de un medico a otro\n");
        printf("\n¿A que medico desea realizar esta accion?");
        printf("\n(Escriba el nombre del medico)");

        do {
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            fread(&medicos, sizeof(Medico), 1, ptrmedicos);
            printf("Lista de medicos\n");

            do {
                printf("\n%s ", medicos.nombre);
                fread(&medicos, sizeof(Medico), 1, ptrmedicos);
            } while (feof(ptrmedicos) == 0);

            fclose(ptrmedicos);
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);

            if (strcmp(opc, negativo) != 0) {
                ptrmedicos = fopen("registroMedico.bin", "r+b");
                fread(&medicos, sizeof(Medico), 1, ptrmedicos);
                contador = 1;

                do {
                    if ((strcmp(opc, medicos.nombre) == 0)) {
                        check = 1;
                        if (check == 1) {
                            do {
                                respuesta[0] = '0';
                                printf("¿Estas seguro de transferir los pacientes de este medico?");
                                ptrpacientes = fopen("registroPaciente.bin", "rb");
                                printf("\nLista de pacientes:");
                                fread(&pac, sizeof(Paciente), 1, ptrpacientes);

                                do {
                                    if (strcmp(medicos.nombre, pac.medico) == 0) {
                                        printf("\n%s ", pac.nombre);
                                    }
                                    fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                                } while (feof(ptrpacientes) == 0);

                                fclose(ptrpacientes);
                                printf("\n[%s]     1)Si    2)No     ", medicos.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);

                                if (opcion != 1 && opcion != 2) {
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    fflush(stdin);
                                } else {
                                    for (i = 0; i < (int)strlen(respuesta); i++) {
                                        if (!isdigit(respuesta[i])) {
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);

                            if (opcion == 1) {
                                printf("¿A que medico quiere pasarle los pacientes?");
                                rewind(ptrmedicos);
                                fread(&medicos, sizeof(Medico), 1, ptrmedicos);

                                do {
                                    printf("\n%s ", medicos.nombre);
                                    fread(&medicos, sizeof(Medico), 1, ptrmedicos);
                                } while (feof(ptrmedicos) == 0);

                                printf("\n(Si desea detener esta accion escriba 'Salir')\n");
                                fflush(stdin);
                                scanf("%[^\n]%*c", nombreAux);
                                ptrpacientes = fopen("registroPaciente.bin", "rb");
                                fread(&pac, sizeof(Paciente), 1, ptrpacientes);

                                do {
                                    if (strcmp(opc, pac.medico) == 0) {
                                        strcpy(pac.medico, nombreAux);
                                        fseek(ptrpacientes,-(long)sizeof(Paciente),SEEK_CUR);
                                        fwrite(&pac, sizeof(Paciente), 1, ptrpacientes);
                                    }
                                    fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                                } while (feof(ptrpacientes) == 0);

                                fclose(ptrpacientes);
                            }
                        } else {
                            printf("El medico ingresado no tiene pacientes registrados, por lo tanto la accion es imposible de realizar");
                        }
                        break;
                    } else {
                        fread(&medicos, sizeof(Medico), 1, ptrmedicos);
                    }
                } while (feof(ptrmedicos) == 0);

                if (opcion == 0) {
                    printf("Medico no encontrado, intentelo nuevamente");
                }
            } else {
                opcion = 1;
            }

            fclose(ptrmedicos);
        } while (opcion == 0 || opcion == 2);

        printf("Saliendo al menu Gestionar medicos\n");
    }
}

void generarInformesAdministrador(){
    printf("\n-------------- Reporte de Médicos --------------\n");
    FILE *archivo;
    Medico unapersona;
    char estat[20];
    archivo = fopen("registroMedico.bin", "rb");
    if(archivo == NULL){
        printf("\nNo hay médicos registrados por el momento, regrese cuando haya registrado a algún médico\n");
        fclose(archivo);
        return;
    }
    int cont = 0;
    int habi = 0;
    int desh = 0;
    fread(&unapersona, sizeof(Medico),1,archivo);
    while(!feof(archivo)){
        if(unapersona.estado == 1){
            strcpy(estat, "HABILITADO");
            printf("\n Médicos [%d]: %s, Estatus: %s\n",cont + 1, unapersona.nombre, estat);
            habi++;
        }else{
            strcpy(estat, "DESHABILITADO"); 
            printf("\n Médicos [%d]: %s, Estatus: %s\n",cont + 1, unapersona.nombre, estat);
            desh++;
        }
        cont++;
        fread(&unapersona, sizeof(Medico), 1, archivo);
    }
    printf("\n");
    for (int i = 0; i < 50; i++){
       printf("-");
    }
    printf("\n");
    printf("La cantidad de médicos son: %d\n", cont);
    for (int i = 0; i < 50; i++){
       printf("-");
    }
    printf("\n");
    printf("La cantidad de médicos inactivos son: %d\n", desh);
    for (int i = 0; i < 50; i++){
       printf("-");
    }
    printf("\n");
    printf("La cantidad de médicos activos son: %d\n", habi);
    fclose(archivo);
    printf("\n");
    continuar();
}

void continuar(){
    int conti;
    printf("Presione 1 + Enter para continuar: \n\n");
    scanf("%d%*c", &conti);
}

void loginMedico(){ 
    printf("\nLogin Médico\n");
    Medico Med;
    char nombreA[100];
    char nombreL[100];
    int intentos = 0;
    do{
        printf("Ingrese su nombre:");
        scanf("%[^\n]%*c", nombreA);
        printf("Ingrese su cédula:");
        scanf("%[^\n]%*c", nombreL);
        Med = validarloginmed(nombreA,nombreL);
        if (Med.estado == -100){
            printf("\nNo hay ningún médico registrado por el momento\n");
            return;
        }
        intentos++;
        if(intentos == 3){
            printf("\nHaz alcanzado el máximo de intentos\n");
            return;
        }
    }while(Med.estado == 100);
    menuMedico(&Med);
}

Medico validarloginmed(char nombre[100], char login[100]){
    FILE *archivo;
    Medico Med;
    int existe = 0;
    archivo = fopen("registroMedico.bin", "rb");
    if(archivo == NULL){
        Med.estado = -100;
        return Med;
    }
    fread(&Med, sizeof(Medico), 1, archivo);
    while(!feof(archivo)){
        if((strcmp(nombre, Med.nombre) == 0) && (strcmp(login, Med.login) == 0)){
            existe = 1;
            break;
        }
        fread(&Med, sizeof(Medico),1,archivo);
    }
    fclose(archivo);
    if (existe == 1){
        return Med;
    }else{
        Med.estado = 100;
        return Med;
    }
}

void menuMedico(Medico *ptrmedico){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          Bienvenido %s!\n", ptrmedico->nombre);
        printf("\n¿Qué acción desea realizar? (Seleccione el número de la acción)");
        printf("\n1) Modificar información personal");
        printf("\n2) Gestionar Pacientes");
        printf("\n3) Generar Informes");
        printf("\n4) Salir\n");
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if((opcion > 0 && opcion < 5)){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (opcion){
                case 1:
                    modificarInformacionMedico(&ptrmedico);
                    break;
                case 2:
                    gestionarPaciente(ptrmedico);
                    break;
                case 3:
                    generarInformesMedico();
                    break;
                case 4:
                    printf("Cerrando sesión...\n");
                    break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 4 || opcion == 0);
}

void modificarInformacionMedico(Medico **medico){
    Medico medicoBuscado, aux;
    int opcion, longitud, i;
    char opc[100];
    char contra[100];
    strcpy(medicoBuscado.nombre, (*medico)->nombre);
    printf("\n              Modificar información personal\n");
    printf("\nNombre: %s", (*medico)->nombre);
    printf("\nCédula: %s", (*medico)->cedula);
    printf("\nDirección: %s", (*medico)->direccion);
    printf("\nTeléfono: %s", (*medico)->telefono);
    printf("\nCorreo electrónico: %s", (*medico)->correo);
    printf("\nContraseña: %s", (*medico)->login);
    do{
        printf("\nSi desea cambiar su información personal presione 1, de lo contrario presione 2: ");
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if (opcion != 1 && opcion != 2){
            printf("El dato ingresado no es valido, por favor intentalo nuevamente");
            fflush(stdin);
        }else{
            for(i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente");
                    opcion = 0;
                    break;
                }
            }
        }
    } while (opcion != 1 && opcion != 2);
    printf("Si desea omitir algún dato menos la contraseña solo presiona Enter\n");  
    if (opcion == 1){
        printf("\nIngrese el nuevo nombre completo: ");
        scanf("%[^\n]%*c", (*medico)->nombre);
        fflush(stdin);
        do{
            do{
                printf("Ingrese la nueva contraseña (Ingrese mínimo 5 caracteres): ");
                scanf("%[^\n]%*c", (*medico)->login);
                fflush(stdin);
                longitud = strlen((*medico)->login);
                if (longitud < 5){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                }
            } while (longitud < 5);
            printf("Vuelva a ingresar la nueva contraseña: ");
            scanf("%[^\n]%*c", contra);
            fflush(stdin);
            if (strcmp((*medico)->login, contra) != 0){
                printf("Las contraseñas no coinciden, intentalo nuevamente\n");
            }
        } while (strcmp((*medico)->login, contra) != 0);
        do{
            printf("Cédula profesional (8 caracteres): ");
            scanf("%[^\n]%*c", (*medico)->cedula);
            fflush(stdin);
            longitud = strlen((*medico)->cedula);
            if (longitud != 8){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            }
        } while (longitud != 8);
        printf("Dirección: ");
        scanf("%[^\n]%*c", (*medico)->direccion);
        fflush(stdin);
        do{
            printf("Teléfono(10 dígitos): ");
            scanf("%[^\n]%*c", (*medico)->telefono);
            fflush(stdin);
            if(strlen((*medico)->telefono) == 10){
                for (i = 0; i < (int)strlen((*medico)->telefono); i++){
                    if(!isdigit((*medico)->telefono[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                    opcion = 1;
                }
            }else{
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                opcion = 0;
            }
        }while(opcion != 1);
        printf("Correo electrónico: ");
        scanf("%[^\n]%*c", (*medico)->correo);
        fflush(stdin);
        printf("Información actualizada con éxito\n");
        FILE *modMedico = fopen("registroMedico.bin", "r+b");
        fread(&aux, sizeof(Medico), 1, modMedico);
        do{
            if(strcmp(aux.nombre, medicoBuscado.nombre) == 0){
                fseek(modMedico,-(long)sizeof(Medico),SEEK_CUR);
                fwrite(*medico, sizeof(Medico), 1, modMedico);
                break;
            }
            fread(&aux, sizeof(Medico), 1, modMedico);
        } while (feof(modMedico) == 0);
        fclose(modMedico);
        FILE *modName = fopen("registroPaciente.bin", "r+b");
        Paciente auxiliar;
        fread(&auxiliar, sizeof(Paciente), 1, modName);
        do{
            if(strcmp(auxiliar.medico, medicoBuscado.nombre) == 0){
                FILE *lectura = fopen("registroPaciente.bin", "r+b");
                Paciente auxiliar2;
                strcpy(auxiliar.medico, (*medico)->nombre);
                fread(&auxiliar2, sizeof(Paciente), 1, lectura);
                do{
                    if(strcmp(auxiliar2.medico, medicoBuscado.nombre) == 0){
                        fseek(lectura,-(long)sizeof(Paciente),SEEK_CUR);
                        fwrite(&auxiliar, sizeof(Paciente), 1, lectura);
                        break;
                    }
                    fread(&auxiliar2, sizeof(Paciente), 1, lectura);
                } while (feof(lectura) == 0);
                fclose(lectura);
            }
            fread(&auxiliar, sizeof(Paciente), 1, modName);
        } while (feof(modName) == 0);
        fclose(modName);
    }
}

void gestionarPaciente(Medico *medico){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          Gestionar Pacientes\n");
        printf("\n¿Qué acción desea realizar? (Seleccione el número de la acción)");
        printf("\n1) Registrar a un nuevo paciente");
        printf("\n2) Actualizar informacion de un paciente");
        printf("\n3) Habilitar o deshabilitar a un paciente");
        printf("\n4) Evaluar pacientes");
        printf("\n5) Elminar a un paciente");
        printf("\n6) Salir\n");
        fflush(stdin);
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if(opcion > 0 && opcion < 7){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (opcion){
                case 1:
                    registrarPaciente(medico);
                    break;
                case 2:
                    actualizarInformacionPaciente(medico);
                    break;
                case 3:
                    cambiarEstatusPaciente(medico);
                    break;
                case 4:
                    evaluarPaciente(medico);
                    break;
                case 5:
                    eliminarPaciente(medico);
                break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 6 || opcion == 0);
}

void registrarPaciente(Medico *medico){
    printf("\nDatos del nuevo paciente\n");
    Paciente pac;
    FILE *registrarPaciente;
    int opcion, i, longitud;
    char opc[100];
    char negativo[] = ("NO");
    registrarPaciente = fopen("registroPaciente.bin", "rb");
    if (registrarPaciente == NULL){
        fclose(registrarPaciente);
        registrarPaciente = fopen("registroPaciente.bin", "wb");
        fclose(registrarPaciente);
    }
    fclose(registrarPaciente);
    printf("\nIngrese los datos del paciente:\n");
    pac.estado = 1;
    strcpy(pac.medico, medico->nombre);
    do{
        printf("Nombre completo: ");
        scanf("%[^\n]%*c", pac.nombre);  
        do{
            opc[0] = '0';
            printf("¿Continuar con el siguiente nombre [%s]?", pac.nombre);
            printf("\n1)Si          2)No          ");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            opcion = atoi(opc);
            fflush(stdin);
            if (opcion != 1 && opcion != 2){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                fflush(stdin);
            }else{
                for(i = 0; i < (int)strlen(opc); i++){
                    if(!isdigit(opc[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                }
            }
        } while (opcion != 1 && opcion != 2);
    } while (opcion == 2);
    do{
        do{
            strcpy(pac.nss, negativo);
            printf("Numero de seguridad social (11 caracteres): ");
            scanf("%[^\n]%*c", pac.nss);
            fflush(stdin);
            longitud = strlen(pac.nss);
            if (longitud != 11){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            }
        } while (longitud != 11);
        do{
            opc[0] = '0';
            printf("¿Continuar con el siguiente NSS [%s]?", pac.nss);
            printf("\n1)Si          2)No          ");
            scanf("%[^\n]%*c", opc);
            opcion = atoi(opc);
            fflush(stdin);
            if (opcion != 1 && opcion != 2){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                fflush(stdin);
            }else{
                for(i = 0; i <(int)strlen(opc); i++){
                    if(!isdigit(opc[i])){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        opcion = 0;
                        break;
                    }
                }
            }
        } while (opcion != 1 && opcion != 2);
    } while (opcion == 2);
    strcpy(pac.login, pac.nss);
    fflush(stdin);
    do{
        printf("Teléfono(10 dígitos): ");
        fflush(stdin);
        scanf("%[^\n]%*c", pac.telefono);
        if(strlen(pac.telefono) == 10){
            for (i = 0; i < (int)strlen(pac.telefono); i++){
                if(!isdigit(pac.telefono[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
                opcion = 1;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            opcion = 0;
        }
    }while(opcion != 1);
    printf("Correo electrónico: ");
    fflush(stdin);
    scanf("%[^\n]%*c", pac.correo);
    registrarPaciente = fopen("registroPaciente.bin", "ab");
    fseek(registrarPaciente, sizeof(Paciente), SEEK_END);
    fwrite(&pac, sizeof(Paciente), 1, registrarPaciente);
    fclose(registrarPaciente);
}

void actualizarInformacionPaciente(Medico *medico){
    Paciente pac, pacienteBuscado;
    FILE *ptrpacientes = fopen("registroPaciente.bin", "rb");
    int opcion, i;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrpacientes == NULL){
        printf("\nNo hay pacientes registrados por el momento, regrese cuando haya registrado algún paciente\n");
        fclose(ptrpacientes);
    }else{
        fclose(ptrpacientes);
        printf("\n                     Actualizar datos\n");
        printf("\n¿De qué paciente desea actualizar los datos?");
        printf("\n(Escriba el nombre del paciente)");
        do{
            opc[0] = '0';
            ptrpacientes = fopen("registroPaciente.bin", "rb");
            printf("\nLista de pacientes:");
            fread(&pac, sizeof(Paciente), 1, ptrpacientes);
            do{
                if (strcmp(medico->nombre, pac.medico) == 0){
                    printf("\n%s ", pac.nombre);
                }
                fread(&pac, sizeof(Paciente), 1, ptrpacientes);
            } while (feof(ptrpacientes) == 0);
            fclose(ptrpacientes);
            printf("\n(Si desea detener ésta acción escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrpacientes = fopen("registroPaciente.bin", "r+b");
                fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                do{
                    if ((strcmp(opc, pac.nombre) == 0) && (strcmp(medico->nombre, pac.medico) == 0)){
                        strcpy(pacienteBuscado.nombre, pac.nombre);
                        printf("\n              Modificar información personal\n");
                        printf("\nNombre: %s", pac.nombre);
                        printf("\nNSS: %s", pac.nss);
                        printf("\nTeléfono: %s", pac.telefono);
                        printf("\nCorreo electrónico: %s", pac.correo);
                        printf("\nContraseña: %s", pac.login);
                        printf("\nSi desea omitir algún dato menos la contraseña solo presiona Enter\n");  
                            do{
                                respuesta[0] = '0';
                                printf("¿Estás seguro de actualizar la información de éste paciente?");
                                printf("\n[%s]     1)Si    2)No     ", pac.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);
                                if (opcion != 1 && opcion != 2){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    fflush(stdin);
                                }else{
                                    for (i = 0; i < (int)strlen(respuesta); i++){
                                        if (!isdigit(respuesta[i])){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);
                            if (opcion == 1){
                                int opcion, longitud, i;
                                char contra[100];
                                printf("\nIngrese el nuevo nombre completo: ");
                                scanf("%[^\n]%*c", pac.nombre);
                                fflush(stdin);
                                    do{
                                        do{
                                            printf("Ingrese la nueva contraseña (Ingrese mínimo 5 caracteres): ");
                                            scanf("%[^\n]%*c", pac.login);
                                            fflush(stdin);
                                            longitud = strlen(pac.login);
                                            if (longitud < 5){
                                                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            }
                                        } while (longitud < 5);
                                    printf("Vuelva a ingresar la nueva contraseña: ");
                                    scanf("%[^\n]%*c", contra);
                                    fflush(stdin);
                                    if (strcmp(pac.login, contra) != 0){
                                        printf("Las contraseñas no coinciden, intentalo nuevamente\n");
                                    }
                                    } while (strcmp(pac.login, contra) != 0);
                                    do{
                                        printf("Número de seguridad social NSS (11 caracteres): ");
                                        scanf("%[^\n]%*c", pac.nss);
                                        fflush(stdin);
                                        longitud = strlen(pac.nss);
                                        if (longitud != 11){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                        }
                                    } while (longitud != 11);
                                    fflush(stdin);
                                    do{
                                        printf("Teléfono(10 dígitos): ");
                                        scanf("%[^\n]%*c", pac.telefono);
                                        fflush(stdin);
                                        if(strlen(pac.telefono) == 10){
                                            for (i = 0; i < (int)strlen(pac.telefono); i++){
                                                if(!isdigit(pac.telefono[i])){
                                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                                    opcion = 0;
                                                    break;
                                                }
                                                opcion = 1;
                                            }
                                        }else{
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                        }
                                    }while(opcion != 1);
                                    printf("Correo electrónico: ");
                                    scanf("%[^\n]%*c", pac.correo);
                                    fflush(stdin);
                                    printf("Información actualizada con éxito\n");
                                    fseek(ptrpacientes,-(long)sizeof(Paciente),SEEK_CUR);
                                    fwrite(&pac, sizeof(Paciente), 1, ptrpacientes);

                                FILE *modName = fopen("registroCuestionarios.bin", "r+b");
                                Cuestionarios auxiliar;
                                fread(&auxiliar, sizeof(Cuestionarios), 1, modName);
                                do{
                                    if(strcmp(auxiliar.paciente, pacienteBuscado.nombre) == 0){
                                        FILE *lectura = fopen("registroCuestionarios.bin", "r+b");
                                        Cuestionarios auxiliar2;
                                        strcpy(auxiliar.paciente, pac.nombre);
                                        fread(&auxiliar2, sizeof(Cuestionarios), 1, lectura);
                                        do{
                                            if(strcmp(auxiliar2.paciente, pacienteBuscado.nombre) == 0){
                                                fseek(lectura,-(long)sizeof(Cuestionarios),SEEK_CUR);
                                                fwrite(&auxiliar, sizeof(Cuestionarios), 1, lectura);
                                                break;
                                            }
                                            fread(&auxiliar2, sizeof(Cuestionarios), 1, lectura);
                                        } while (feof(lectura) == 0);
                                        fclose(lectura);
                                    }
                                    fread(&auxiliar, sizeof(Cuestionarios), 1, modName);
                                } while (feof(modName) == 0);
                                fclose(modName);
                            }   
                        break;
                    }else{
                        fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                        opcion = 0;
                    }
                } while (feof(ptrpacientes) == 0);
                if (opcion == 0){
                    printf("Paciente no encontrado, inténtelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrpacientes);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menú Gestionar pacientes\n");
    }
}

void cambiarEstatusPaciente(Medico *medico){
    Paciente pac;
    FILE *ptrpacientes = fopen("registroPaciente.bin", "rb");
    int opcion, i;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrpacientes == NULL){
        printf("\nNo hay pacientes registrados por el momento, regrese cuando haya registrado a algún paciente\n");
        fclose(ptrpacientes);
    }else{
        fclose(ptrpacientes);
        printf("\n                     Habilitar o deshabilitar\n");
        printf("\n¿Qué paciente desea habilitar o deshabilitar?");
        printf("\n(Escriba el nombre del paciente)");
        do{
            opc[0] = '0';
            ptrpacientes = fopen("registroPaciente.bin", "rb");
            printf("\nLista de pacientes:");
            fread(&pac, sizeof(Paciente), 1, ptrpacientes);
            do{
                if (strcmp(medico->nombre, pac.medico) == 0){
                    printf("\n%s ", pac.nombre);
                    if (pac.estado == 1){
                        printf("(Habilitado)");
                    }
                    if (pac.estado == 0){
                        printf("(Deshabilitado)");
                    }
                }
                fread(&pac, sizeof(Paciente), 1, ptrpacientes);
            } while (feof(ptrpacientes) == 0);
            fclose(ptrpacientes);
            printf("\n(Si desea detener esta acción escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrpacientes = fopen("registroPaciente.bin", "r+b");
                fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                do{
                    if ((strcmp(opc, pac.nombre) == 0) && (strcmp(medico->nombre, pac.medico) == 0)){
                        if (pac.estado == 1){
                            do{
                                respuesta[0] = '0';
                                printf("¿Está seguro de inhabilitar a este paciente?");
                                printf("\n[%s]     1)Si    2)No     ", pac.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);
                                if (opcion != 1 && opcion != 2){
                                    printf("El dato ingresado no es valido, por favor inténtelo nuevamente\n");
                                    fflush(stdin);
                                }else{
                                    for (i = 0; i < (int)strlen(respuesta); i++){
                                        if (!isdigit(respuesta[i])){
                                            printf("El dato ingresado no es valido, por favor inténtelo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);
                            if (opcion == 1){
                                pac.estado = 0;
                                fseek(ptrpacientes,-(long)sizeof(Paciente),SEEK_CUR);
                                fwrite(&pac, sizeof(Paciente), 1, ptrpacientes);
                                printf("Deshabilitado!\n");
                            }
                        }else{
                            if (pac.estado == 0){
                                do{
                                    respuesta[0] = '0';
                                    printf("¿Estas seguro de habilitar a este paciente?");
                                    printf("\n[%s]     1)Si    2)No     ", pac.nombre);
                                    fflush(stdin);
                                    scanf("%[^\n]%*c", respuesta);
                                    opcion = atoi(respuesta);
                                    fflush(stdin);
                                    if (opcion != 1 && opcion != 2){
                                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                        fflush(stdin);
                                    }else{
                                        for (i = 0; i < (int)strlen(respuesta); i++){
                                            if (!isdigit(respuesta[i])){
                                                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                                opcion = 0;
                                                break;
                                            }
                                        }
                                    }
                                } while (opcion != 1 && opcion != 2);
                                if (opcion == 1){
                                    pac.estado = 1;
                                    fseek(ptrpacientes,-(long)sizeof(Paciente),SEEK_CUR);
                                    fwrite(&pac, sizeof(Paciente), 1, ptrpacientes);
                                    printf("Habilitado!\n");
                                }
                            }
                        }
                        break;
                    }else{
                        fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                        opcion = 0;
                    }
                } while (feof(ptrpacientes) == 0);
                if (opcion == 0){
                    printf("Paciente no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrpacientes);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menú Gestionar pacientes\n");
    }
}

void evaluarPaciente(Medico *medico){
    Paciente pac;
    FILE *ptrpacientes = fopen("registroPaciente.bin", "rb");
    int opcion;
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrpacientes == NULL){
        printf("\nNo hay pacientes registrados por el momento, regrese cuando haya registrado a algún paciente\n");
        fclose(ptrpacientes);
    }else{
        fclose(ptrpacientes);
        printf("\nEvaluar pacientes\n");
        printf("\n¿Qué paciente desea evaluar?");
        printf("\n(Escriba el nombre del paciente)");
        do
        {
            opc[0] = '0';
            ptrpacientes = fopen("registroPaciente.bin", "rb");
            printf("\nLista de pacientes:");
            fread(&pac, sizeof(Paciente), 1, ptrpacientes);
            do{
                if (strcmp(medico->nombre, pac.medico) == 0){
                    printf("\n%s ", pac.nombre);
                }
                fread(&pac, sizeof(Paciente), 1, ptrpacientes);
            } while (feof(ptrpacientes) == 0);
            fclose(ptrpacientes);
            printf("\n(Si desea detener esta acción escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrpacientes = fopen("registroPaciente.bin", "r+b");
                fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                do{
                    if ((strcmp(opc, pac.nombre) == 0) && (strcmp(medico->nombre, pac.medico) == 0)){
                        evaluacion(&pac);
                        opcion = 2;
                        break;
                    }else{
                        fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                        opcion = 0;
                    }
                } while (feof(ptrpacientes) == 0);
                if (opcion == 0){
                    printf("Paciente no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrpacientes);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menú Gestionar pacientes\n");
    }
}

void evaluacion(Paciente *ptrpaciente){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          %s\n", ptrpaciente->nombre);
        printf("\n¿Qué acción desea realizar? (Seleccione el número de la acción)");
        printf("\n1) Registrar consulta (Se registrará la fecha de hoy)");
        printf("\n2) Agregar observaciones o recomendaciones");
        printf("\n3) Asignar cuestionario");
        printf("\n4) Ver resultados de los cuestionarios");
        printf("\n5) Salir\n");
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if((opcion > 0 && opcion < 6)){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (opcion){
                case 1:
                    registrarConsulta(ptrpaciente);
                    break;
                case 2:
                    observaciones(ptrpaciente);
                    break;
                case 3:
                    asignarCuestionarios(ptrpaciente);
                    break;
                case 4:
                    verResultados(ptrpaciente);
                    break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 5 || opcion == 0);
}

void registrarConsulta(Paciente *ptrpaciente){
    time_t fecha;
    Cuestionarios regFecha, comparacion;
    FILE *ptrCuestionarios;
    int opcion;
    char day1[3];
    char month1[4];
    char year1[5];
    char day2[3];
    char month2[4];
    char year2[5];
    time(&fecha);
    strcpy(comparacion.fecha, ctime(&fecha));
    strncpy(day1, (char*)&comparacion.fecha[8], 2);
    strncpy(month1, (char*)&comparacion.fecha[4], 3);
    strncpy(year1, (char*)&comparacion.fecha[20], 4);
    ptrCuestionarios = fopen("registroCuestionarios.bin", "rb");
    if (ptrCuestionarios == NULL){
        fclose(ptrCuestionarios);
        ptrCuestionarios = fopen("registroCuestionarios.bin", "wb");
        fclose(ptrCuestionarios);
    }
    ptrCuestionarios = fopen("registroCuestionarios.bin", "r+b");
    fread(&regFecha, sizeof(Cuestionarios), 1, ptrCuestionarios);
    do{
        strncpy(day2, (char*)&regFecha.fecha[8], 2);
        strncpy(month2, (char*)&regFecha.fecha[4], 3);
        strncpy(year2, (char*)&regFecha.fecha[20], 4);
        if ((strcmp(day1, day2) == 0) && (strcmp(month1, month2) == 0) && (strcmp(year1, year2) == 0) && strcmp(ptrpaciente->nombre, regFecha.paciente) == 0){
            opcion = 0;
            break;
        }else{
            fread(&regFecha, sizeof(Cuestionarios), 1, ptrCuestionarios);
            opcion = 1;
        }
    } while (feof(ptrCuestionarios) == 0);
    fclose(ptrCuestionarios);
    if (opcion == 1){
        ptrCuestionarios = fopen("registroCuestionarios.bin", "ab");
        strcpy(comparacion.paciente, ptrpaciente->nombre);
        fwrite(&comparacion, sizeof(Cuestionarios), 1, ptrCuestionarios);
        fclose(ptrCuestionarios);
    }
    if (opcion == 0){
        printf("\nSolo puede registrar una cita por día\n");
    }
}

void observaciones(Paciente *ptrpaciente){
    FILE *ptrCuestionarios = fopen("registroCuestionarios.bin", "rb");
    Cuestionarios cues;
    int opcion, i, cont;
    char respuesta[100];
    char negativo[] = ("Salir");
    if (ptrCuestionarios == NULL){
        printf("\nNo hay consulta registrada, vuelva cuando haya registrado alguna.\n");
        fclose(ptrCuestionarios);
        return;
    }
    fclose(ptrCuestionarios);
    printf("\n¿En qué fecha desea agregar observaciones?\n");
    do{
        cont = 1;
        printf("\nEscriba el número de la fecha de la consulta\n");
        ptrCuestionarios = fopen("registroCuestionarios.bin", "rb");
        fread(&cues, sizeof(Cuestionarios), 1, ptrCuestionarios);
        do{
            if (strcmp(ptrpaciente->nombre, cues.paciente) == 0){
                printf("%d) %s", cont, cues.fecha);
                cont++;
            }
            fread(&cues, sizeof(Cuestionarios), 1, ptrCuestionarios);
        } while (feof(ptrCuestionarios) == 0);
        fclose(ptrCuestionarios);
        printf("(Si desea detener esta acción escriba 'Salir')\n");
        fflush(stdin);
        scanf("%[^\n]%*c", respuesta);
        opcion = atoi(respuesta);
        fflush(stdin);   
        if (strcmp(respuesta, negativo) == 0){
            return;
        }
        if (opcion < 1 || opcion > (cont - 1)){
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            opcion = 0;
            fflush(stdin);
        }else{
            for (i = 0; i < (int)strlen(respuesta); i++){
                if (!isdigit(respuesta[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
        }
    } while (opcion == 0);
    cont = 1;
    FILE *ptrcues = fopen("registroCuestionarios.bin", "r+b");
    fread(&cues, sizeof(Cuestionarios), 1, ptrcues);
    do{
        if (strcmp(ptrpaciente->nombre, cues.paciente) == 0){
            if (opcion == cont){
                fseek(ptrcues, -(long)sizeof(Cuestionarios), SEEK_CUR);
                printf("A continuación escriba las observaciones o recomendaciones que desee agregar\n");
                fflush(stdin);
                scanf("%[^\n]%*c", cues.observaciones);
                fflush(stdin);
                fwrite(&cues, sizeof(Cuestionarios), 1, ptrCuestionarios);
                fclose(ptrcues);
                printf("Agregado de forma exitosa\n");
                return;
            }else{
                cont++;
            }
        }
        fread(&cues, sizeof(Cuestionarios), 1, ptrcues);
    } while (feof(ptrcues) == 0);
}

void asignarCuestionarios(Paciente *ptrpaciente){
    FILE *ptrCuestionarios = fopen("registroCuestionarios.bin", "rb");
    Cuestionarios cues;
    int opcion, i, cont;
    char respuesta[100];
    char negativo[] = ("Salir");
    if (ptrCuestionarios == NULL){
        printf("\nNo hay consulta registrada, vuelva cuando haya registrado alguna.\n");
        fclose(ptrCuestionarios);
        return;
    }
    fclose(ptrCuestionarios);
    printf("\n¿En qué fecha desea agregar un cuestionario?\n");
    do{
        cont = 1;
        printf("\nEscriba el número de la fecha de la consulta\n");
        ptrCuestionarios = fopen("registroCuestionarios.bin", "rb");
        fread(&cues, sizeof(Cuestionarios), 1, ptrCuestionarios);
        do{
            if ((strcmp(ptrpaciente->nombre, cues.paciente) == 0) && (cues.estado == 0)){
                printf("%d) %s", cont, cues.fecha);
                cont++;
            }
            fread(&cues, sizeof(Cuestionarios), 1, ptrCuestionarios);
        } while (feof(ptrCuestionarios) == 0);
        fclose(ptrCuestionarios);
        printf("(Si desea detener esta accion escriba 'Salir')\n");
        fflush(stdin);
        scanf("%[^\n]%*c", respuesta);
        opcion = atoi(respuesta);
        fflush(stdin);   
        if (strcmp(respuesta, negativo) == 0){
            return;
        }
        if (opcion < 1 || opcion > (cont - 1)){
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            opcion = 0;
            fflush(stdin);
        }else{
            for (i = 0; i < (int)strlen(respuesta); i++){
                if (!isdigit(respuesta[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
        }
    } while (opcion == 0);
    cont = 1;
    FILE *ptrcues = fopen("registroCuestionarios.bin", "r+b");
    fread(&cues, sizeof(Cuestionarios), 1, ptrcues);
    do{
        if ((strcmp(ptrpaciente->nombre, cues.paciente) == 0) && (cues.estado == 0)){
            if (opcion == cont){
                fseek(ptrcues, -(long)sizeof(Cuestionarios), SEEK_CUR);
                do{
                    printf("Escriba el número del cuestionario que desea agregar");
                    printf("\n1) Cuestionario de Beck");
                    printf("\n2) Cuestionario de Depresión Mayor (MDI)");
                    printf("\n3) Cuestionario de de Zung");
                    printf("\n4) Cuestionario PHQ-9");
                    printf("\n5) Salir\n");
                    fflush(stdin);
                    scanf("%[^\n]%*c", respuesta);
                    fflush(stdin);
                    cues.cuestionario = atoi(respuesta);
                    fflush(stdin);   
                    if (cues.cuestionario < 1 || cues.cuestionario > 5){
                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                        cues.cuestionario = 0;
                        fflush(stdin);
                    }else{
                        for (i = 0; i < (int)strlen(respuesta); i++){
                            if (!isdigit(respuesta[i])){
                                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                cues.cuestionario = 0;
                                break;
                            }
                        }
                    }
                } while (cues.cuestionario == 0);
                cues.estado = 0;
                fwrite(&cues, sizeof(Cuestionarios), 1, ptrCuestionarios);
                fclose(ptrcues);
                printf("Agregado de forma exitosa\n");
                break;
            }else{
                cont++;
            }
        }
        fread(&cues, sizeof(Cuestionarios), 1, ptrcues);
    } while (feof(ptrcues) == 0);
}

void verResultados(Paciente *ptrpaciente){
    printf("\nVer resultados\n");
    FILE *ptrCuestionarios = fopen("registroCuestionarios.bin", "rb");
    FILE *ptrBeck;
    FILE *ptrZung;
    FILE *ptrMDI;
    FILE *ptrPhq9;
    Cuestionarios cues;
    Beck preg;
    MDI pregu;
    Zung pregun;
    Phq9 pregunt;
    int i;
    /*
    int opcion, i, cont;
    char respuesta[100];
    char negativo[] = ("Salir");
    */
    if (ptrCuestionarios == NULL){
        printf("\nNo hay consulta registrada, vuelva cuando haya registrado alguna.\n");
        fclose(ptrCuestionarios);
        return;
    }
    fclose(ptrCuestionarios);
    ptrCuestionarios = fopen("registroCuestionarios.bin", "rb");
    fread(&cues, sizeof(Cuestionarios), 1, ptrCuestionarios);
    do{
        if (cues.cuestionario == 1 && cues.estado == 1 && strcmp(cues.paciente, ptrpaciente->nombre) == 0){
            ptrBeck = fopen("registroBeck.bin", "rb");
            if (ptrBeck != NULL){
                fread(&preg, sizeof(Beck), 1, ptrBeck);
                do{
                    if ((strcmp(cues.paciente, preg.paciete) == 0) && (strcmp(cues.fecha, preg.fecha) == 0)){
                        printf("\nFecha de la consulta %s", cues.fecha);
                        printf("Cuestionario de beck, puntuación: %d/63", cues.puntuacion);
                        if (cues.puntuacion <= 13){
                            printf("\nDepresión leve");
                        }
                        if (cues.puntuacion >= 14 && cues.puntuacion <= 19){
                            printf("\nDepresión moderada");
                        }
                        if (cues.puntuacion >= 20 && cues.puntuacion <= 28){
                            printf("\nDepresión moderada-severa");
                        }
                        if (cues.puntuacion >= 29){
                            printf("\nDepresión severa");
                        }
                        printf("\nRespuestas");
                        for (i = 0; i < 21; i++){
                            printf("\n%s", preg.pregunta[i].pregunta);
                            printf("\n%s", preg.respuesta[i].respuesta);
                        }
                        printf("\n");
                    }
                    fread(&preg, sizeof(Beck), 1, ptrBeck);
                } while (feof(ptrBeck) == 0);
                fclose(ptrBeck);
            }
        }
        if (cues.cuestionario == 2 && cues.estado == 1 && strcmp(cues.paciente, ptrpaciente->nombre) == 0){
            ptrMDI = fopen("registroMDI.bin", "rb");
            if (ptrZung != NULL){
                fread(&pregu, sizeof(MDI), 1, ptrMDI);
                do{
                    if ((strcmp(cues.paciente, pregu.paciete) == 0) && (strcmp(cues.fecha, pregu.fecha) == 0)){
                        printf("\nFecha de la consulta %s", cues.fecha);
                        printf("Cuestionario de MDI, puntuación: %d/65", cues.puntuacion);
                        if (cues.puntuacion <= 19){
                            printf("\nSin depresión");
                        }
                        if (cues.puntuacion >= 20 && cues.puntuacion <= 24){
                            printf("\nDepresión leve");
                        }
                        if (cues.puntuacion >= 25 && cues.puntuacion <= 29){
                            printf("\nDepresión moderada");
                        }
                        if (cues.puntuacion >= 30){
                            printf("\nDepresión severa");
                        }
                        printf("\nRespuestas");
                        for (i = 0; i < 13; i++){
                            printf("\n%s", pregu.pregunta[i].pregunta);
                            printf("\n%s", pregu.respuesta[i].respuesta);
                        }
                        printf("\n");
                    }
                    fread(&pregu, sizeof(MDI), 1, ptrMDI);
                } while (feof(ptrMDI) == 0);
                fclose(ptrMDI);
            }
        }
        if (cues.cuestionario == 3 && cues.estado == 1 && strcmp(cues.paciente, ptrpaciente->nombre) == 0){
            ptrZung = fopen("registroZung.bin", "rb");
            if (ptrZung != NULL){
                fread(&pregun, sizeof(Zung), 1, ptrZung);
                do{
                    if ((strcmp(cues.paciente, pregun.paciete) == 0) && (strcmp(cues.fecha, pregun.fecha) == 0)){
                        printf("\nFecha de la consulta %s", cues.fecha);
                        printf("Cuestionario de Zung, puntuación: %d/57", cues.puntuacion);
                        if (cues.puntuacion <= 28){
                            printf("\nAusencia de depresión");
                        }
                        if (cues.puntuacion >= 29 && cues.puntuacion <= 41){
                            printf("\nDepresión leve");
                        }
                        if (cues.puntuacion >= 42 && cues.puntuacion <= 53){
                            printf("\nDepresión moderada");
                        }
                        if (cues.puntuacion >= 54){
                            printf("\nDepresión grave");
                        }
                        printf("\nRespuestas");
                        for (i = 0; i < 19; i++){
                            printf("\n%s", pregun.pregunta[i].pregunta);
                            printf("\n%s", pregun.respuesta[i].respuesta);
                        }
                        printf("\n");
                    }
                    fread(&pregun, sizeof(Zung), 1, ptrZung);
                } while (feof(ptrZung) == 0);
                fclose(ptrZung);
            }
        }
        if (cues.cuestionario == 4 && cues.estado == 1 && strcmp(cues.paciente, ptrpaciente->nombre) == 0){
            ptrPhq9 = fopen("registroPHQ9.bin", "rb");
            if (ptrPhq9 != NULL){
                fread(&pregunt, sizeof(Phq9), 1, ptrPhq9);
                do{
                    if ((strcmp(cues.paciente, pregunt.paciete) == 0) && (strcmp(cues.fecha, pregunt.fecha) == 0)){
                        printf("\nFecha de la consulta %s", cues.fecha);
                        printf("Cuestionario de PHQ9, puntuación: %d/27", cues.puntuacion);
                        if (cues.puntuacion <= 4){
                            printf("\nDepresión mínima");
                        }
                        if (cues.puntuacion >= 5 && cues.puntuacion <= 9){
                            printf("\nDepresión leve");
                        }
                        if (cues.puntuacion >= 10 && cues.puntuacion <= 14){
                            printf("\nDepresión moderada");
                        }
                        if (cues.puntuacion >= 15 && cues.puntuacion <= 19){
                            printf("\nDepresión moderada-severa");
                        }
                        if (cues.puntuacion >= 20){
                            printf("\nDepresión severa");
                        }
                        printf("\nRespuestas");
                        for (i = 0; i < 9; i++){
                            printf("\n%s", pregunt.pregunta[i].pregunta);
                            printf("\n%s", pregunt.respuesta[i].respuesta);
                        }
                        printf("\n");
                    }
                    fread(&pregunt, sizeof(Phq9), 1, ptrPhq9);
                } while (feof(ptrPhq9) == 0);
                fclose(ptrPhq9);
            }
        }
        fread(&cues, sizeof(Cuestionarios), 1, ptrCuestionarios);
    } while (feof(ptrCuestionarios) == 0);
}

void eliminarPaciente(Medico *medico){
    Paciente paciente, copiaPaciente;
    FILE *ptrpaciente = fopen("registroPaciente.bin", "rb");
    int opcion, i, contador;
    char respuesta[100];
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrpaciente == NULL){
        printf("\nNo hay pacientes registrados por el momento, regrese cuando haya registrado algún paciente\n");
        fclose(ptrpaciente);
    }else{
        fclose(ptrpaciente);
        printf("\n                     Eliminar paciente\n");
        printf("\n¿Qué paciente desea eliminar?");
        printf("\n(Escriba el nombre del paciente)");
        do{
            opc[0] = '0';
            ptrpaciente = fopen("registroPaciente.bin", "rb");
            fread(&paciente, sizeof(Paciente), 1, ptrpaciente);
            do{
                if (strcmp(medico->nombre, paciente.medico) == 0){
                    printf("\n%s ", paciente.nombre);
                }
                fread(&paciente, sizeof(Paciente), 1, ptrpaciente);
            } while (feof(ptrpaciente) == 0);
            fclose(ptrpaciente);
            printf("\n(Si desea detener esta acción escriba 'Salir')\n");
            fflush(stdin);    
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrpaciente = fopen("registroPaciente.bin", "r+b");
                fread(&copiaPaciente, sizeof(Paciente), 1, ptrpaciente);
                contador = 1;
                do{
                    if ((strcmp(opc, copiaPaciente.nombre) == 0)&&(strcmp(medico->nombre, copiaPaciente.medico) == 0)){
                            do{
                                respuesta[0] = '0';
                                printf("¿Estas seguro de eliminar a este paciente?");
                                printf("\n[%s]     1)Sí    2)No     ", copiaPaciente.nombre);
                                fflush(stdin);
                                scanf("%[^\n]%*c", respuesta);
                                opcion = atoi(respuesta);
                                fflush(stdin);
                                if (opcion != 1 && opcion != 2){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    fflush(stdin);
                                }else{
                                    for (i = 0; i < (int)strlen(respuesta); i++){
                                        if (!isdigit(respuesta[i])){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                            opcion = 0;
                                            break;
                                        }
                                    }
                                }
                            } while (opcion != 1 && opcion != 2);
                            if (opcion == 1){
                                FILE *copiaptrPaciente = fopen("registroPacienteCopia.bin", "wb");;
                                fseek(ptrpaciente, contador *-(long)sizeof(Paciente), SEEK_CUR);
                                fread(&paciente, sizeof(Paciente), 1, ptrpaciente);
                                do{
                                    if(strcmp(copiaPaciente.nombre, paciente.nombre) != 0){
                                        fwrite(&paciente, sizeof(Paciente), 1, copiaptrPaciente);
                                    }
                                    fread(&paciente, sizeof(Paciente), 1, ptrpaciente);
                                } while (feof(ptrpaciente) == 0);
                                fclose(ptrpaciente);
                                fclose(copiaptrPaciente);
                                remove("registroPaciente.bin");
                                rename("registroPacienteCopia.bin", "registroPaciente.bin");
                            }
                        break;
                    }else{
                        fread(&copiaPaciente, sizeof(Paciente), 1, ptrpaciente);
                        opcion = 0;
                        contador++;
                    }
                } while (feof(ptrpaciente) == 0);
                if (opcion == 0){
                    printf("Paciente no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrpaciente);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menú Gestionar pacientes\n");
    }
}

//corregir
//corregir
//corregir
//corregir
//corregir
//corregir
//corregir
//corregir
//corregir
//corregir

void generarInformesMedico(){
    printf("\nSeleccionado Generar Informes\n");
    FILE *archivo;
    Paciente unapersona;
    char estat[40];
    archivo = fopen("registroPaciente.bin", "rb");
    if(archivo == NULL){
        printf("\nNo hay pacientes registrados por el momento, regrese cuando haya registrado algún medico\n");
        fclose(archivo);
        return;
    }
    int cont = 0;
    int habi = 0;
    int desh = 0;
    fread(&unapersona, sizeof(Paciente),1,archivo);
    while(!feof(archivo)){
        if(unapersona.estado == 1){
            strcpy(estat, "Aún en consulta");
            printf("\n Médicos [%d]: %s, Estatus: %s\n",cont + 1, unapersona.nombre, estat);
            habi++;
        }else{
            strcpy(estat, "Alta"); 
            printf("\n Médicos [%d]: %s, Estatus: %s\n",cont + 1, unapersona.nombre, estat);
            desh++;
        }
        cont++;
        fread(&unapersona, sizeof(Paciente), 1, archivo);
    }
    printf("\n");
    for (int i = 0; i < 50; i++){
       printf("-");
    }
    printf("\n");
    printf("La cantidad de Pacientes son: %d\n", cont);
    for (int i = 0; i < 50; i++){
       printf("-");
    }
    printf("\n");
    printf("La cantidad de Pacientes dados de alta son: %d\n", desh);
    for (int i = 0; i < 50; i++){
       printf("-");
    }
    printf("\n");
    printf("La cantidad de Pacientes aun tomando conulta son: %d\n", habi);
    fclose(archivo);
    printf("\n");
    continuar();
}

void loginPaciente(){
    printf("\nLogin Paciente\n");
    Paciente Pac;
    char nombreA[100];
    char nombreL[100];
    int intentos = 0;
    do{
        printf("Ingrese su nombre:");
        scanf("%[^\n]%*c", nombreA);
        printf("Ingrese su cedula:");
        scanf("%[^\n]%*c", nombreL);
        Pac = validarloginpaci(nombreA,nombreL);
        if (Pac.estado == -100){
            printf("\nNo hay ningún médico registrado por el momento\n");
            return;
        }
        intentos++;
        if(intentos == 3){
            printf("\nHaz alcanzado el máximo de intentos\n");
            return;
        }
    }while(Pac.estado == 100);
    menuPaciente(&Pac);
}

Paciente validarloginpaci(char nombre[100], char login[100]){
    FILE *archivo;
    Paciente Pacie;
    int existe = 0;
    archivo = fopen("registroPaciente.bin", "rb");
    if(archivo == NULL){
        Pacie.estado = -100;
        return Pacie;
    }
    fread(&Pacie, sizeof(Paciente), 1, archivo);
    while(!feof(archivo)){
        if((strcmp(nombre, Pacie.nombre) == 0)&&(strcmp(login, Pacie.login) == 0)){
            existe = 1;
            break;
        }
        fread(&Pacie, sizeof(Paciente),1,archivo);
    }
    fclose(archivo);
    if (existe == 1){
        return Pacie;
    }else{
        Pacie.estado = 100;
        return Pacie;
    }
}

void menuPaciente(Paciente *ptrpac){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          Bienvenido %s!\n", ptrpac->nombre);
        printf("\n¿Qué acción desea realizar? (Seleccione el número de la acción)");
        printf("\n1) Responder Cuestionarios");
        printf("\n2) Visualizar datos de las consultas");
        printf("\n3) Salir\n");
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if((opcion > 0 && opcion < 4)){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (opcion){
                case 1:
                    responderCuestionarios(ptrpac);
                    break;
                case 2:
                    generarInformesPaciente(ptrpac);
                    break;
                case 3:
                    printf("Cerrando sesión...\n");
                    break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 3 || opcion == 0);
}

void responderCuestionarios(Paciente *ptrpac){
    printf("\nResponder Cuestionaros\n");
    FILE *BECK = fopen("registroBeck.bin", "rb");
    if (BECK == NULL){
        fclose(BECK);
        BECK = fopen("registroBeck.bin", "wb");
        fclose(BECK);
    }
    fclose(BECK);
    FILE *ZUNG = fopen("registroZung.bin", "rb");
    if (ZUNG == NULL){
        fclose(ZUNG);
        ZUNG = fopen("registroZung.bin", "wb");
        fclose(ZUNG);
    }
    fclose(ZUNG);
    FILE *mdi = fopen("registroMDI.bin", "rb");
    if (mdi == NULL){
        fclose(mdi);
        mdi = fopen("registroMDI.bin", "wb");
        fclose(mdi);
    }
    fclose(mdi);
    FILE *PHQ9 = fopen("registroPHQ9.bin", "rb");
    if (PHQ9 == NULL){
        fclose(PHQ9);
        PHQ9 = fopen("registroPHQ9.bin", "wb");
        fclose(PHQ9);
    }
    fclose(PHQ9);
    FILE *cuestionario = fopen("registroCuestionarios.bin", "rb");
    Cuestionarios cues;
    Beck beck;
    Zung zung;
    MDI Mdi;
    Phq9 phq9;
    int opcion, i, cont, respuesta, puntuacion, lecturas;
    int repeticiones[100];
    char opc[100];
    char resp[100];
    struct test{
        int test;
    }Preguntas[100];
    if (cuestionario == NULL){
        printf("\nNo hay consulta registrada, vuelva cuando haya registrado alguna.\n");
        fclose(cuestionario);
        return;
    }
    fclose(cuestionario);
    do{
        printf("\nSeleccione el número del cuestionario que desea responder.");
        cont = 0;
        cuestionario = fopen("registroCuestionarios.bin", "r+b");
        fread(&cues, sizeof(Cuestionarios), 1, cuestionario);
        lecturas = 1;
        while(!feof(cuestionario)){
            if(cues.estado == 0 && strcmp(cues.paciente, ptrpac->nombre) == 0){
                switch (cues.cuestionario){
                    case 1:
                        repeticiones[cont] = lecturas;
                        cont++;
                        printf("\n%d) Cuestionario de beck", cont);
                        Preguntas[cont-1].test = 1;
                        break;
                    case 2:
                        repeticiones[cont] = lecturas;
                        cont++;
                        printf("\n%d) Cuestionario de Depresión Mayor (MDI)", cont);
                        Preguntas[cont-1].test = 2;
                        break;
                    case 3:
                        repeticiones[cont] = lecturas;
                        cont++;
                        printf("\n%d) Cuestionario de de Zung", cont);
                        Preguntas[cont-1].test = 3;
                        break;
                    case 4:
                        repeticiones[cont] = lecturas;
                        cont++;
                        printf("\n%d) Cuestionario PHQ-9", cont);
                        Preguntas[cont-1].test = 4;
                        break;
                }
            }
            fread(&cues, sizeof(Cuestionarios), 1, cuestionario);
            lecturas ++;
        }
        if (cont == 0){
            printf("\nNo tienes ningún cuestionario asignado por el momento\n");
            return;
        }
        printf("\n");
        fflush(stdin);
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if((opcion > 0 && opcion <= cont)){
            for (i = 0; i < (int)strlen(opc); i++){
                if(!isdigit(opc[i])){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                    opcion = 0;
                    break;
                }
            }
            switch (Preguntas[opcion-1].test){
                case 1:
                    puntuacion = 0;
                    printf("\nIngrese el número de la respuesta que mejor describa su situación");
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n1-. Qué tan triste te sintes?");
                        strcpy(beck.pregunta[0].pregunta, "1-. Qué tan triste te sintes?");
                        printf("\n1) No me siento triste");
                        printf("\n2) Me siento triste gran parte del tiempo");
                        printf("\n3) Me siento triste todo el tiempo");
                        printf("\n4) Me siento tan triste o soy tan infeliz que no puedo soportarlo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[0].respuesta, "No me siento triste");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[0].respuesta, "Me siento triste gran parte del tiempo");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[0].respuesta, "Me siento triste todo el tiempo");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[0].respuesta, "Me siento tan triste o soy tan infeliz que no puedo soportarlo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n2-. Cuál es tu nivel de pesimismo?");
                        strcpy(beck.pregunta[1].pregunta, "2-. Cuál es tu nivel de pesimismo?");
                        printf("\n1) No estoy desalentado respecto de mi futuro");
                        printf("\n2) Me siento más desalentado respecto de mi futuro que lo que solía estarlo");
                        printf("\n3) No espero que las cosas funcionen para mi");
                        printf("\n4) Siento que no hay esperanza para mi futuro y que sólo puede empeorar\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[1].respuesta, "No estoy desalentado respecto de mi futuro");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[1].respuesta, "Me siento más desalentado respecto de mi futuro que lo que solía estarlo");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[1].respuesta, "No espero que las cosas funcionen para mi");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[1].respuesta, "Siento que no hay esperanza para mi futuro y que sólo puede empeorar");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n3-. Sientes que haz fracasado?");
                        strcpy(beck.pregunta[2].pregunta, "3-. Sientes que haz fracasado?");
                        printf("\n1) No me siento como un fracasado");
                        printf("\n2) He fracasado más de lo que hubiera debido");
                        printf("\n3) Cuando miro hacia atrás, veo muchos fracasos");
                        printf("\n4) Siento que como persona soy un fracaso total\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[2].respuesta, "No me siento como un fracasado");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[2].respuesta, "He fracasado más de lo que hubiera debido");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[2].respuesta, "Cuando miro hacia atrás, veo muchos fracasos");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[2].respuesta, "Siento que como persona soy un fracaso total");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n4-. Haz tenido pérdida de placer?");
                        strcpy(beck.pregunta[3].pregunta, "4-. Haz tenido pérdida de placer?");
                        printf("\n1) Obtengo tanto placer como siempre por las cosas de las que disfruto");
                        printf("\n2) No disfruto tanto de las cosas como solía hacerlo");
                        printf("\n3) Obtengo muy poco placer de las cosas que solía disfrutar");
                        printf("\n4) No puedo obtener ningún placer de las cosas de las que solía disfrutar\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[3].respuesta, "Obtengo tanto placer como siempre por las cosas de las que disfruto");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[3].respuesta, "No disfruto tanto de las cosas como solía hacerlo");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[3].respuesta, "Obtengo muy poco placer de las cosas que solía disfrutar");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[3].respuesta, "No puedo obtener ningún placer de las cosas de las que solía disfrutar");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n5-. Tienes sentimientos de culpa?");
                        strcpy(beck.pregunta[4].pregunta, "5-. Tienes sentimientos de culpa?");
                        printf("\n1) No me siento particularmente culpable");
                        printf("\n2) Me siento culpable respecto de varias cosas que he hecho o que debería haber hecho");
                        printf("\n3) Me siento bastante culpable la mayor parte del tiempo");
                        printf("\n4) Me siento culpable todo el tiempo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[4].respuesta, "No me siento particularmente culpable");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[4].respuesta, "Me siento culpable respecto de varias cosas que he hecho o que debería haber hecho");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[4].respuesta, "Me siento bastante culpable la mayor parte del tiempo");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[4].respuesta, "Me siento culpable todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n6-. Haz tenido sentimientos de castigo?");
                        strcpy(beck.pregunta[5].pregunta, "6-. Haz tenido sentimientos de castigo?");
                        printf("\n1) No siento que este siendo castigado");
                        printf("\n2) Siento que tal vez pueda ser castigado");
                        printf("\n3) Espero ser castigado");
                        printf("\n4) Siento que estoy siendo castigado\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[5].respuesta, "No siento que este siendo castigado");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[5].respuesta, "Siento que tal vez pueda ser castigado");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[5].respuesta, "Espero ser castigado");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[5].respuesta, "Siento que estoy siendo castigado");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n7-. Sientes disconformidad de ti mismo?");
                        strcpy(beck.pregunta[6].pregunta, "7-. Sientes disconformidad de ti mismo?");
                        printf("\n1) Siento acerca de mi lo mismo que siempre");
                        printf("\n2) He perdido la confianza en mí mismo");
                        printf("\n3) Estoy decepcionado conmigo mismo");
                        printf("\n4) No me gusto a mí mismo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[6].respuesta, "Siento acerca de mi lo mismo que siempre");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[6].respuesta, "He perdido la confianza en mí mismo");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[6].respuesta, "Estoy decepcionado conmigo mismo");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[6].respuesta, "No me gusto a mí mismo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n8-. Te autocriticas?");
                        strcpy(beck.pregunta[7].pregunta, "8-. Te autocriticas?");
                        printf("\n1) No me critico ni me culpo más de lo habitual");
                        printf("\n2) Estoy más crítico conmigo mismo de lo que solía estarlo");
                        printf("\n3) Me critico a mí mismo por todos mis errores");
                        printf("\n4) Me culpo a mí mismo por todo lo malo que sucede\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[7].respuesta, "No me critico ni me culpo más de lo habitual");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[7].respuesta, "Estoy más crítico conmigo mismo de lo que solía estarlo");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[7].respuesta, "Me critico a mí mismo por todos mis errores");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[7].respuesta, "Me culpo a mí mismo por todo lo malo que sucede");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n9-. Haz tenido pensamientos o deseos suicidas?");
                        strcpy(beck.pregunta[8].pregunta, "9-. Haz tenido pensamientos o deseos suicidas?");
                        printf("\n1) No tengo ningún pensamiento de matarme");
                        printf("\n2) He tenido pensamientos de matarme, pero no lo haría");
                        printf("\n3) Querría matarme");
                        printf("\n4) Me mataría si tuviera la oportunidad de hacerlo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[8].respuesta, "No tengo ningún pensamiento de matarme");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[8].respuesta, "He tenido pensamientos de matarme, pero no lo haría");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[8].respuesta, "Querría matarme");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[8].respuesta, "Me mataría si tuviera la oportunidad de hacerlo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n10-. Qué tanto has llorado últimamente?");
                        strcpy(beck.pregunta[9].pregunta, "10-. Qué tanto has llorado últimamente?");
                        printf("\n1) No lloro más de lo que solía hacerlo");
                        printf("\n2) Lloro más de lo que solía hacerlo");
                        printf("\n3) Lloro por cualquier pequeñez");
                        printf("\n4) Siento ganas de llorar pero no puedo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[9].respuesta, "No lloro más de lo que solía hacerlo");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[9].respuesta, "Lloro más de lo que solía hacerlo");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[9].respuesta, "Lloro por cualquier pequeñez");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[9].respuesta, "Siento ganas de llorar pero no puedo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n11-. Te haz sentido inquieto o agitado?");
                        strcpy(beck.pregunta[10].pregunta, "11-. Te haz sentido inquieto o agitado?");
                        printf("\n1) No estoy más inquieto o tenso que lo habitual");
                        printf("\n2) Me siento más inquieto o tenso que lo habitual");
                        printf("\n3) Estoy tan inquieto o agitado que me es difícil quedarme quieto");
                        printf("\n4) Estoy tan inquieto o agitado que tengo que estar siempre en movimiento o haciendo algo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[10].respuesta, "No estoy más inquieto o tenso que lo habitual");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[10].respuesta, "Me siento más inquieto o tenso que lo habitual");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[10].respuesta, "Estoy tan inquieto o agitado que me es difícil quedarme quieto");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[10].respuesta, "Estoy tan inquieto o agitado que tengo que estar siempre en movimiento o haciendo algo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n12-. Haz tenido pérdida de interés?");
                        strcpy(beck.pregunta[11].pregunta, "12-. Haz tenido pérdida de interés?");
                        printf("\n1) No he perdido el interés en otras actividades o personas");
                        printf("\n2) Estoy menos interesado que antes en otras personas o cosas");
                        printf("\n3) He perdido casi todo el interés en otras personas o cosas");
                        printf("\n4) Me es difícil interesarme por algo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[11].respuesta, "No he perdido el interés en otras actividades o personas");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[11].respuesta, "Estoy menos interesado que antes en otras personas o cosas");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[11].respuesta, "He perdido casi todo el interés en otras personas o cosas");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[11].respuesta, "Me es difícil interesarme por algo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n13-. Cómo es tu toma de decisiones?");
                        strcpy(beck.pregunta[12].pregunta, "13-. Cómo es tu toma de decisiones?");
                        printf("\n1) Tomo mis propias decisiones tan bien como siempre");
                        printf("\n2) Me resulta más difícil que de costumbre tomar decisiones");
                        printf("\n3) Encuentro mucha más dificultad que antes para tomar decisiones");
                        printf("\n4) Tengo problemas para tomar cualquier decisión\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[12].respuesta, "Tomo mis propias decisiones tan bien como siempre");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[12].respuesta, "Me resulta más difícil que de costumbre tomar decisiones");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[12].respuesta, "Encuentro mucha más dificultad que antes para tomar decisiones");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[12].respuesta, "Tengo problemas para tomar cualquier decisión");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n14-. Te sientes valioso?");
                        strcpy(beck.pregunta[13].pregunta, "14-. Te sientes valioso?");
                        printf("\n1) No siento que yo no sea valioso");
                        printf("\n2) No me considero a mi mismo tan valioso y útil como solía considerarme");
                        printf("\n3) Me siento menos valioso cuando me comparo con otros");
                        printf("\n4) Siento que no valgo nada\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[13].respuesta, "No siento que yo no sea valioso");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[13].respuesta, "No me considero a mi mismo tan valioso y útil como solía considerarme");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[13].respuesta, "Me siento menos valioso cuando me comparo con otros");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[13].respuesta, "Siento que no valgo nada");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n15-. Tienes pérdida de energia?");
                        strcpy(beck.pregunta[14].pregunta, "15-. Tienes pérdida de energia?");
                        printf("\n1) Tengo tanta energía como siempre");
                        printf("\n2) Tengo menos energía que la que solía tener");
                        printf("\n3) No tengo suficiente energía para hacer demasiado");
                        printf("\n4) No tengo energía suficiente para hacer nada\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[14].respuesta, "Tengo tanta energía como siempre");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[14].respuesta, "Tengo menos energía que la que solía tener");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[14].respuesta, "No tengo suficiente energía para hacer demasiado");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[14].respuesta, "No tengo energía suficiente para hacer nada");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n16-. Haz experimentado cambios en tus hábitos de sueño?");
                        strcpy(beck.pregunta[15].pregunta, "16-. Haz experimentado cambios en tus hábitos de sueño?");
                        printf("\n1) No he experimentado ningún cambio en mis hábitos de sueño");
                        printf("\n2) Duermo un poco menos que lo habitual");
                        printf("\n3) Duermo mucho menos que lo habitual");
                        printf("\n4) Me despierto 1-2 horas más temprano y no puedo volver a dormirme\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[15].respuesta, "No he experimentado ningún cambio en mis hábitos de sueño");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[15].respuesta, "Duermo un poco menos que lo habitual");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[15].respuesta, "Duermo mucho menos que lo habitual");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[15].respuesta, "Me despierto 1-2 horas más temprano y no puedo volver a dormirme");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n17-. Qué tan irritable te haz sentido?");
                        strcpy(beck.pregunta[16].pregunta, "17-. Qué tan irritable te haz sentido?");
                        printf("\n1) No estoy tan irritable que lo habitual");
                        printf("\n2) Estoy más irritable que lo habitual");
                        printf("\n3) Estoy mucho más irritable que lo habitual");
                        printf("\n4) Estoy irritable todo el tiempo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[16].respuesta, "No estoy tan irritable que lo habitual");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[16].respuesta, "Estoy más irritable que lo habitual");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[16].respuesta, "Estoy mucho más irritable que lo habitual");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[16].respuesta, "Estoy irritable todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n18-. Haz tenido cambios en el apetito?");
                        strcpy(beck.pregunta[17].pregunta, "18-. Haz tenido cambios en el apetito?");
                        printf("\n1) No he experimentado ningún cambio en mi apetito");
                        printf("\n2) Mi apetito es un poco menor que lo habitual");
                        printf("\n3) Mi apetito es mucho menor que antes");
                        printf("\n4) No tengo apetito en absoluto\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[17].respuesta, "No he experimentado ningún cambio en mi apetito");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[17].respuesta, "Mi apetito es un poco menor que lo habitual");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[17].respuesta, "Mi apetito es mucho menor que antes");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[17].respuesta, "No tengo apetito en absoluto");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n19-. Haz tenido dificultad de concentración?");
                        strcpy(beck.pregunta[18].pregunta, "19-. Haz tenido dificultad de concentración?");
                        printf("\n1) Puedo concentrarme tan bien como siempre");
                        printf("\n2) No puedo concentrarme tan bien como habitualmente");
                        printf("\n3) Me es difícil mantener la mente en algo por mucho tiempo");
                        printf("\n4) Encuentro que no puedo concentrarme en nada\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[18].respuesta, "Puedo concentrarme tan bien como siempre");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[18].respuesta, "No puedo concentrarme tan bien como habitualmente");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[18].respuesta, "Me es difícil mantener la mente en algo por mucho tiempo");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[18].respuesta, "Encuentro que no puedo concentrarme en nada");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n20-. Te sientes cansado o fatigado?");
                        strcpy(beck.pregunta[19].pregunta, "20-. Te sientes cansado o fatigado?");
                        printf("\n1) No estoy más cansado o fatigado que lo habitual");
                        printf("\n2) Me fatigo o me canso más fácilmente que lo habitual");
                        printf("\n3) Estoy demasiado fatigado o cansado para hacer muchas de las cosas que solía hacer");
                        printf("\n4) Estoy demasiado fatigado o cansado para hacer la mayoría de las cosas que solía hacer\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[19].respuesta, "No estoy más cansado o fatigado que lo habitual");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[19].respuesta, "Me fatigo o me canso más fácilmente que lo habitual");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[19].respuesta, "Estoy demasiado fatigado o cansado para hacer muchas de las cosas que solía hacer");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[19].respuesta, "Estoy demasiado fatigado o cansado para hacer la mayoría de las cosas que solía hacer");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n21-. Haz tenido pérdida de interés en el sexo?");
                        strcpy(beck.pregunta[20].pregunta, "21-. Haz tenido pérdida de interés en el sexo?");
                        printf("\n1) No he notado ningún cambio reciente en mi interés por el sexo");
                        printf("\n2) Estoy menos interesado en el sexo de lo que solía estarlo");
                        printf("\n3) Estoy mucho menos interesado en el sexo");
                        printf("\n4) He perdido completamente el interés en el sexo\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(beck.respuesta[20].respuesta, "No he notado ningún cambio reciente en mi interés por el sexo");
                                    break;
                                case 2:
                                    strcpy(beck.respuesta[20].respuesta, "Estoy menos interesado en el sexo de lo que solía estarlo");
                                    break;
                                case 3:
                                    strcpy(beck.respuesta[20].respuesta, "Estoy mucho menos interesado en el sexo");
                                    break;
                                case 4:
                                    strcpy(beck.respuesta[20].respuesta, "He perdido completamente el interés en el sexo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    rewind(cuestionario);
                    for ( i = 0; i < repeticiones[opcion-1]; i++){
                        fread(&cues, sizeof(Cuestionarios), 1, cuestionario);
                    }
                    fseek(cuestionario, -(long)sizeof(Cuestionarios), SEEK_CUR);
                    cues.estado = 1;
                    cues.puntuacion = puntuacion;
                    strcpy(beck.fecha, cues.fecha);
                    strcpy(beck.paciete, ptrpac->nombre);
                    fwrite(&cues, sizeof(Cuestionarios), 1, cuestionario);
                    fclose(cuestionario);
                    BECK = fopen("registroBeck.bin", "ab");
                    fwrite(&beck, sizeof(Beck), 1, BECK);
                    fclose(BECK);
                    break;
                case 2:
                    puntuacion = 0;
                    printf("\nIngrese el número de la respuesta que mejor describa su situación");
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n1-. ¿Se ha sentido deprimido o triste?");
                        strcpy(Mdi.pregunta[0].pregunta, "1-. ¿Se ha sentido deprimido o triste?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[0].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[0].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[0].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[0].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[0].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[0].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n2-. ¿Ha perdido interés en sus actividades diarias?");
                        strcpy(Mdi.pregunta[1].pregunta, "2-. ¿Ha perdido interés en sus actividades diarias?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[1].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[1].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[1].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[1].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[1].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[1].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n3-. ¿Ha sentido falta de energía y fuerza?");
                        strcpy(Mdi.pregunta[2].pregunta, "3-. ¿Ha sentido falta de energía y fuerza?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[2].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[2].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[2].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[2].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[2].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[2].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n4-. ¿Ha sentido menos confianza en sí mismo?");
                        strcpy(Mdi.pregunta[3].pregunta, "4-. ¿Ha sentido menos confianza en sí mismo?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[3].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[3].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[3].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[3].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[3].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[3].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n5-. ¿Ha tenido usted cargos de conciencia o sentimientos de culpa?");
                        strcpy(Mdi.pregunta[4].pregunta, "5-. ¿Ha tenido usted cargos de conciencia o sentimientos de culpa?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[4].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[4].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[4].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[4].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[4].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[4].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n6-. ¿Ha sentido que la vida no merece la pena vivirla?");
                        strcpy(Mdi.pregunta[5].pregunta, "6-. ¿Ha sentido que la vida no merece la pena vivirla?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[5].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[5].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[5].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[5].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[5].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[5].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n7-. ¿Ha tenido dificultades para concentrarse?");
                        strcpy(Mdi.pregunta[6].pregunta, "7-. ¿Ha tenido dificultades para concentrarse?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[6].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[6].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[6].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[6].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[6].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[6].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n8-. ¿Se ha sentido muy inquieto?");
                        strcpy(Mdi.pregunta[7].pregunta, "8-. ¿Se ha sentido muy inquieto?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[7].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[7].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[7].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[7].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[7].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[7].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n9-. ¿Se ha sentido apagado o lento?");
                        strcpy(Mdi.pregunta[8].pregunta, "9-. ¿Se ha sentido apagado o lento?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[8].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[8].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[8].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[8].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[8].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[8].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n10-. ¿Has estado durmiendo muy poco?");
                        strcpy(Mdi.pregunta[9].pregunta, "10-. ¿Has estado durmiendo muy poco?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[9].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[9].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[9].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[9].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[9].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[9].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n11-. ¿Has estado durmiendo demasiado?");
                        strcpy(Mdi.pregunta[10].pregunta, "11-. ¿Has estado durmiendo demasiado?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[10].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[10].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[10].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[10].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[10].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[10].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n12-. ¿Ha notado falta de apetito?");
                        strcpy(Mdi.pregunta[11].pregunta, "12-. ¿Ha notado falta de apetito?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[11].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[11].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[11].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[11].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[11].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[11].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n13-. ¿Ha notado aumento de apetito?");
                        strcpy(Mdi.pregunta[12].pregunta, "13-. ¿Ha notado aumento de apetito?");
                        printf("\n1) Nunca");
                        printf("\n2) Ocasionalmente");
                        printf("\n3) Poco menos de la mitad del tiempo");
                        printf("\n4) Poco más de la mitad del tiempo");
                        printf("\n5) La mayor parte del tiempo");
                        printf("\n6) Todo el tiempo");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        fflush(stdin);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 7)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(Mdi.respuesta[12].respuesta, "Nunca");
                                    break;
                                case 2:
                                    strcpy(Mdi.respuesta[12].respuesta, "Ocasionalmente");
                                    break;
                                case 3:
                                    strcpy(Mdi.respuesta[12].respuesta, "Poco menos de la mitad del tiempo");
                                    break;
                                case 4:
                                    strcpy(Mdi.respuesta[12].respuesta, "Poco más de la mitad del tiempo");
                                    break;
                                case 5:
                                    strcpy(Mdi.respuesta[12].respuesta, "La mayor parte del tiempo");
                                    break;
                                case 6:
                                    strcpy(Mdi.respuesta[12].respuesta, "Todo el tiempo");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    rewind(cuestionario);
                    for ( i = 0; i < repeticiones[opcion-1]; i++){
                        fread(&cues, sizeof(Cuestionarios), 1, cuestionario);
                    }
                    fseek(cuestionario, -(long)sizeof(Cuestionarios), SEEK_CUR);
                    cues.estado = 1;
                    cues.puntuacion = puntuacion;
                    strcpy(Mdi.fecha, cues.fecha);
                    strcpy(Mdi.paciete, ptrpac->nombre);
                    fwrite(&cues, sizeof(Cuestionarios), 1, cuestionario);
                    fclose(cuestionario);
                    mdi = fopen("registroMDI.bin", "ab");
                    fwrite(&Mdi, sizeof(MDI), 1, mdi);
                    fclose(mdi);
                    break;
                case 3:
                    puntuacion = 0;
                    printf("\nIngrese el numero de la respuesta que mejor describa su situacion");
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n1-. Me siento triste y deprimido");
                        strcpy(zung.pregunta[0].pregunta, "1-. Me siento triste y deprimido");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[0].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[0].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[0].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[0].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n2-. Por las mañanas me siento mejor que por las tardes");
                        strcpy(zung.pregunta[1].pregunta, "2-. Por las mañanas me siento mejor que por las tardes");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[1].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[1].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[1].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[1].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n3-. Frecuentemente tengo ganas de llorar y a veces lloro");
                        strcpy(zung.pregunta[2].pregunta, "3-. Frecuentemente tengo ganas de llorar y a veces lloro");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[2].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[2].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[2].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[2].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n4-. Me cuesta mucho dormir o duermo mal por las noches");
                        strcpy(zung.pregunta[3].pregunta, "4-. Me cuesta mucho dormir o duermo mal por las noches");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[3].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[3].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[3].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[3].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n5-. Ahora tengo tanto apetito como antes");
                        strcpy(zung.pregunta[4].pregunta, "5-. Ahora tengo tanto apetito como antes");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[4].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[4].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[4].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[4].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n6-. Creo que estoy adelgazando");
                        strcpy(zung.pregunta[5].pregunta, "6-. Creo que estoy adelgazando");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[5].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[5].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[5].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[5].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n7-. Estoy estreñido");
                        strcpy(zung.pregunta[6].pregunta, "7-. Estoy estreñido");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[6].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[6].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[6].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[6].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n8-. Tengo palpitaciones");
                        strcpy(zung.pregunta[7].pregunta, "8-. Tengo palpitaciones");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[7].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[7].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[7].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[7].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n9-. Me canso por cualquier cosa");
                        strcpy(zung.pregunta[8].pregunta, "9-. Me canso por cualquier cosa");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[8].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[8].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[8].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[8].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n10-. Mi cabeza está tan despejada como antes");
                        strcpy(zung.pregunta[9].pregunta, "10-. Mi cabeza está tan despejada como antes");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[9].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[9].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[9].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[9].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n11-. Hago las cosas con la misma facilidad que antes");
                        strcpy(zung.pregunta[10].pregunta, "11-. Hago las cosas con la misma facilidad que antes");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[10].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[10].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[10].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[10].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n12-. Me siento agitado e intranquilo y no puedo estar quieto");
                        strcpy(zung.pregunta[11].pregunta, "12-. Me siento agitado e intranquilo y no puedo estar quieto");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[11].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[11].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[11].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[11].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n13-. Tengo esperanza y confío en el futuro");
                        strcpy(zung.pregunta[12].pregunta, "13-. Tengo esperanza y confío en el futuro");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[12].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[12].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[12].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[12].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n14-. Me siento más irritable que habitualmente");
                        strcpy(zung.pregunta[13].pregunta, "14-. Me siento más irritable que habitualmente");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[13].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[13].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[13].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[13].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n15-. Encuentro fácil tomar decisiones");
                        strcpy(zung.pregunta[14].pregunta, "15-. Encuentro fácil tomar decisiones");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[14].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[14].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[14].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[14].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n16-. Me creo útil y necesario para la gente");
                        strcpy(zung.pregunta[15].pregunta, "16-. Me creo útil y necesario para la gente");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[15].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[15].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[15].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[15].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n17-. Encuentro agradable vivir, mi vida es plena");
                        strcpy(zung.pregunta[16].pregunta, "17-. Encuentro agradable vivir, mi vida es plena");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[16].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[16].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[16].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[16].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n18-. Creo que sería mejor para los demás si me muriera");
                        strcpy(zung.pregunta[17].pregunta, "18-. Creo que sería mejor para los demás si me muriera");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[17].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[17].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[17].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[17].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n19-. Me gustan las mismas cosas que solían agradarme");
                        strcpy(zung.pregunta[18].pregunta, "19-. Me gustan las mismas cosas que solían agradarme");
                        printf("\n1) Muy pocas veces");
                        printf("\n2) Algunas veces");
                        printf("\n3) Muchas veces");
                        printf("\n4) Casi siempre\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-4)*(-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(zung.respuesta[18].respuesta, "Muy pocas veces");
                                    break;
                                case 2:
                                    strcpy(zung.respuesta[18].respuesta, "Algunas veces");
                                    break;
                                case 3:
                                    strcpy(zung.respuesta[18].respuesta, "Muchas veces");
                                    break;
                                case 4:
                                    strcpy(zung.respuesta[18].respuesta, "Casi siempre");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    rewind(cuestionario);
                    for ( i = 0; i < repeticiones[opcion-1]; i++){
                        fread(&cues, sizeof(Cuestionarios), 1, cuestionario);
                    }
                    fseek(cuestionario, -(long)sizeof(Cuestionarios), SEEK_CUR);
                    cues.estado = 1;
                    cues.puntuacion = puntuacion;
                    strcpy(zung.fecha, cues.fecha);
                    strcpy(zung.paciete, ptrpac->nombre);
                    fwrite(&cues, sizeof(Cuestionarios), 1, cuestionario);
                    fclose(cuestionario);
                    ZUNG = fopen("registroZung.bin", "ab");
                    fwrite(&zung, sizeof(Zung), 1, ZUNG);
                    fclose(ZUNG);
                    break;
                case 4:
                    puntuacion = 0;
                    printf("\nIngrese el numero de la respuesta que mejor describa su situacion");
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n1-. Poco interés o placer en hacer las cosas");
                        strcpy(phq9.pregunta[0].pregunta, "1-. Poco interés o placer en hacer las cosas");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[0].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[0].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[0].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[0].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n2-. Se ha sentido decaído(a), deprimido(a), o sin esperanzas");
                        strcpy(phq9.pregunta[1].pregunta, "2-. Se ha sentido decaído(a), deprimido(a), o sin esperanzas");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[1].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[1].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[1].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[1].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n3-. Se ha sentido cansado(a) o con poca energía");
                        strcpy(phq9.pregunta[2].pregunta, "3-. Se ha sentido cansado(a) o con poca energía");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[2].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[2].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[2].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[2].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n4-. Se ha sentido cansado(a) o con poca energía");
                        strcpy(phq9.pregunta[3].pregunta, "4-. Se ha sentido cansado(a) o con poca energía");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[3].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[3].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[3].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[3].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n5-. Con poco apetito o ha comido en exceso");
                        strcpy(phq9.pregunta[4].pregunta, "5-. Con poco apetito o ha comido en exceso");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[4].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[4].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[4].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[4].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n6-. Se ha sentido mal con usted mismo(a) o que es un fracaso o que ha quedado mal con usted mismo(a) o con su familia");
                        strcpy(phq9.pregunta[5].pregunta, "6-. Se ha sentido mal con usted mismo(a) o que es un fracaso o que ha quedado mal con usted mismo(a) o con su familia");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[5].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[5].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[5].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[5].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n7-. Ha tenido dificultad para concentrarse en cosas tales como leer el periódico o ver televisión");
                        strcpy(phq9.pregunta[6].pregunta, "7-. Ha tenido dificultad para concentrarse en cosas tales como leer el periódico o ver televisión");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[6].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[6].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[6].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[6].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n8-. ¿Se ha estado moviendo o hablando tan lento que otras personas podrían notarlo?");
                        strcpy(phq9.pregunta[7].pregunta, "8-. ¿Se ha estado moviendo o hablando tan lento que otras personas podrían notarlo?");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[7].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[7].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[7].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[7].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    do{
                        strcpy(resp, "NO");
                        respuesta = 0;
                        printf("\n9-. Ha pensado que estaría mejor muerto(a) o se le ha ocurrido lastimarse de alguna manera");
                        strcpy(phq9.pregunta[8].pregunta, "9-. Ha pensado que estaría mejor muerto(a) o se le ha ocurrido lastimarse de alguna manera");
                        printf("\n1) Para nada");
                        printf("\n2) Varios días");
                        printf("\n3) Más de la mitad de los días");
                        printf("\n4) Casi todos los días\n");
                        fflush(stdin);
                        scanf("%[^\n]%*c", resp);
                        respuesta = atoi(resp);
                        if((respuesta > 0 && respuesta < 5)){
                            for (i = 0; i < (int)strlen(resp); i++){
                                if(!isdigit(opc[i])){
                                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    respuesta = 0;
                                    break;
                                }
                            }
                            puntuacion += (respuesta-1);
                            switch (respuesta){
                                case 1:
                                    strcpy(phq9.respuesta[8].respuesta, "Para nada");
                                    break;
                                case 2:
                                    strcpy(phq9.respuesta[8].respuesta, "Varios días");
                                    break;
                                case 3:
                                    strcpy(phq9.respuesta[8].respuesta, "Más de la mitad de los días");
                                    break;
                                case 4:
                                    strcpy(phq9.respuesta[8].respuesta, "Casi todos los días");
                                    break;
                            }
                        }else{
                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                            fflush(stdin);
                            respuesta = 0;
                        }
                    } while (respuesta == 0);
                    rewind(cuestionario);
                    for ( i = 0; i < repeticiones[opcion-1]; i++){
                        fread(&cues, sizeof(Cuestionarios), 1, cuestionario);
                    }
                    fseek(cuestionario, -(long)sizeof(Cuestionarios), SEEK_CUR);
                    cues.estado = 1;
                    cues.puntuacion = puntuacion;
                    strcpy(phq9.fecha, cues.fecha);
                    strcpy(phq9.paciete, ptrpac->nombre);
                    fwrite(&cues, sizeof(Cuestionarios), 1, cuestionario);
                    fclose(cuestionario);
                    PHQ9 = fopen("registroPHQ9.bin", "ab");
                    fwrite(&phq9, sizeof(Phq9), 1, PHQ9);
                    fclose(PHQ9);
                    break;
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
        fclose(cuestionario);
    } while (opcion == 0);
}

void generarInformesPaciente(Paciente *ptrpac){
    printf("\nSeleccionado Visualizar datos de las consultas de %s\n", ptrpac->nombre);
    FILE *archivo;
    Cuestionarios unapersona;
    char estat[20];
    archivo = fopen("registroCuestionarios.bin", "rb");
    if(archivo == NULL){
        printf("\nNo hay pacientes registrados por el momento, regrese cuando haya registrado a algun medico\n");
        fclose(archivo);
        return;
    }
    int cont = 1;
    int habi = 0;
    int desh = 0;
    printf("Consultas del usuario:");
    fread(&unapersona, sizeof(Cuestionarios),1,archivo);
    while(!feof(archivo)){
        if(strcmp(unapersona.paciente, ptrpac->nombre)){
            if(unapersona.estado == 0){
                strcpy(estat, "NO");
            }else{
                strcpy(estat, "SI");
            }
            printf("Consulta [%d] - Fecha [%s] - Cuestionario respondido: [%d] - Su puntuacion es: %d", cont, unapersona.fecha, unapersona.estado, unapersona.puntuacion);
            cont++;
        }
        fread(&unapersona, sizeof(Cuestionarios), 1, archivo);
    }
    printf("\n");
    continuar();
}