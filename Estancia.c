#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
//Hola
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
void generarInformesPaciente();

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
                printf("\n(Ingrese el numero de usuario que le corresponde)");
                printf("\n1) Administrador");
                printf("\n2) Medico");
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
                            printf("Cerrando programa.");
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
                printf("Cedula profecional(8 caracteres): ");
                scanf("%[^\n]%*c", admin->cedula);
                fflush(stdin);
                longitud = strlen(admin->cedula);
                if (longitud != 8){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                }
            } while (longitud != 8);
            do{
                opc[0] = '0';
                printf("¿Continuar con la siguiente cedula [%s]?", admin->cedula);
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
        printf("Direccion: ");
        fflush(stdin);
        scanf("%[^\n]%*c", admin->direccion);
        do{
            printf("Telefono(10 digitos): ");
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
        printf("Correo electronico: ");
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
        printf("\n              Modificar informacion personal\n");
        printf("\nNombre: %s", admin->nombre);
        printf("\nCedula: %s", admin->cedula);
        printf("\nDireccion: %s", admin->direccion);
        printf("\nTelefono: %s", admin->telefono);
        printf("\nCorreo electronico: %s", admin->correo);
        printf("\nContraseña: %s", admin->login);
        do{
            printf("\nSi desea cambiar su informacion personal presione 1, de lo contrario presione 2: ");
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
        printf("Si deseas omitir algun dato menos la contraseña solo preciona Enter\n");  
        if (opcion == 1){
            printf("\nIngrese el nuevo nombre completo: ");
            scanf("%[^\n]%*c", admin->nombre);
            fflush(stdin);
            do{
                do{
                    printf("Ingrese la nueva contraseña (Ingrese minimo 5 caracteres): ");
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
                printf("Cedula profesional (8 caracteres): ");
                scanf("%[^\n]%*c", admin->cedula);
                fflush(stdin);
                longitud = strlen(admin->cedula);
                if (longitud != 8){
                    printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                }
            } while (longitud != 8);
            printf("Direccion: ");
            scanf("%[^\n]%*c", admin->direccion);
            fflush(stdin);
            do{
                printf("Telefono(10 digitos): ");
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
            printf("Correo electronico: ");
            scanf("%[^\n]%*c", admin->correo);
            fflush(stdin);
            printf("Informacion actualizada con exito\n");
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
        printf("Ingrese su cedula:");
        scanf("%[^\n]%*c", nombreL);
        Admin = validarloginadmin(nombreA,nombreL);
        intentos++;
        if(intentos == 3){
            printf("\nHas alcanzado el maximo de intentos\n");
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
        printf("\n¿Que accion desea realizar? (Seleccione el número de la accion)");
        printf("\n1) Modificar informacion personal");
        printf("\n2) Gestionar Medico");
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
                    printf("Cerrando sesion.\n");
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
        printf("\n          Gestionar Medicos\n");
        printf("\n¿Que accion desea realizar? (Seleccione el número de la accion)");
        printf("\n1) Registrar a un nuevo medico");
        printf("\n2) Actualizar informacion de un medico");
        printf("\n3) Habilitar o deshabilitar a un medico");
        printf("\n4) Elminar a un medico");
        printf("\n5) Salir\n");
        fflush(stdin);
        scanf("%[^\n]%*c", opc);
        opcion = atoi(opc);
        if(opcion > 0 && opcion < 6){
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
            }
        }else{
            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            fflush(stdin);
            opcion = 0;
        }
    }while (opcion != 5 || opcion == 0);
}

void registrarMedico(){
    printf("\n              Registrar a un nuevo medico\n");
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
    printf("\nIngrese los datos del medico:\n");
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
            printf("Cedula profecional(8 caracteres): ");
            scanf("%[^\n]%*c", med.cedula);
            fflush(stdin);
            longitud = strlen(med.cedula);
            if (longitud != 8){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            }
        } while (longitud != 8);
        do{
            opc[0] = '0';
            printf("¿Continuar con la siguiente cedula [%s]?", med.cedula);
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
    printf("Direccion: ");
    fflush(stdin);
    scanf("%[^\n]%*c", med.direccion);
    do{
        printf("Telefono(10 digitos): ");
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
    printf("Correo electronico: ");
    fflush(stdin);
    scanf("%[^\n]%*c", med.correo);
    registrarMedico = fopen("registroMedico.bin", "ab");
    printf("Medico agregado con exito!");
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
        printf("\nNo hay medicos registrados por el momento, regrese cuando alla registrado a algun medico\n");
        fclose(ptrmedicos);
    }else{
        fclose(ptrmedicos);
        printf("\n                     Actualizar datos\n");
        printf("\n¿Que medico desea actualizar los datos?");
        printf("\n(Escriba el nombre del medico)");
        do{
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            printf("\nLista de medicos:");
            fread(&med, sizeof(Medico), 1, ptrmedicos);
            do{
                printf("\n%s ", med.nombre);
                fread(&med, sizeof(Medico), 1, ptrmedicos);
            } while (feof(ptrmedicos) == 0);
            fclose(ptrmedicos);
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrmedicos = fopen("registroMedico.bin", "r+b");
                fread(&med, sizeof(Medico), 1, ptrmedicos);
                do{
                    if (strcmp(opc, med.nombre) == 0){
                        strcpy(medicoBuscado.nombre, med.nombre);
                        printf("\nNombre: %s", med.nombre);
                        printf("\nCedula: %s", med.cedula);
                        printf("\nDireccion: %s", med.direccion);
                        printf("\nTelefono: %s", med.telefono);
                        printf("\nCorreo electronico: %s", med.correo);
                        printf("\nContraseña: %s", med.login);
                        printf("\nSi deseas omitir algun dato menos la contraseña solo preciona Enter\n");  
                            do{
                                respuesta[0] = '0';
                                printf("¿Estas seguro de actualizar la informacion de este medico?");
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
                                printf("\n              Modificar informacion personal\n");
                                printf("\nIngrese el nuevo nombre completo: ");
                                scanf("%[^\n]%*c", med.nombre);
                                fflush(stdin);
                                do{
                                    do{
                                        printf("Ingrese la nueva contraseña (Ingrese minimo 5 caracteres): ");
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
                                    printf("Cedula profesional (8 caracteres): ");
                                    scanf("%[^\n]%*c", med.cedula);
                                    fflush(stdin);
                                    longitud = strlen(med.cedula);
                                    if (longitud != 8){
                                        printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                    }
                                } while (longitud != 8);
                                printf("Direccion: ");
                                scanf("%[^\n]%*c", med.direccion);
                                fflush(stdin);
                                do{
                                    printf("Telefono(10 digitos): ");
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
                                printf("Correo electronico: ");
                                scanf("%[^\n]%*c", med.correo);
                                fflush(stdin);
                                printf("Informacion actualizada con exito\n");
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
                    printf("Medico no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrmedicos);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menu Gestionar medicos\n");
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
        printf("\nNo hay medicos registrados por el momento, regrese cuando alla registrado a algun medico\n");
        fclose(ptrmedicos);
    }else{
        fclose(ptrmedicos);
        printf("\n                     Habilitar o deshabilitar\n");
        printf("\n¿Que medico desea habilitar o deshabilitar?");
        printf("\n(Escriba el nombre del medico)");
        do{
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            printf("\nLista de medicos:");
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
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
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
                                printf("¿Estas seguro de inhabilitar a este medico?");
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
                                printf("Deshabilitado!\n");
                            }
                        }else{
                            if (med.estado == 0){
                                do{
                                    respuesta[0] = '0';
                                    printf("¿Estas seguro de habilitar a este medico?");
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
                                    printf("Habilitado!\n");
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
                    printf("Medico no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrmedicos);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menu Gestionar medicos\n");
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
        printf("\nNo hay medicos registrados por el momento, regrese cuando alla registrado a algun medico\n");
        fclose(ptrmedicos);
    }else{
        fclose(ptrmedicos);
        printf("\n                     Eliminar medico\n");
        printf("\nPara eliminar un medico primero debe deshabilitarlo y tampoco debe tener pacientes registrados a su nombre");
        printf("\n¿Que medico desea eliminar?");
        printf("\n(Escriba el nombre del medico)");
        do{
            opc[0] = '0';
            ptrmedicos = fopen("registroMedico.bin", "rb");
            printf("\nLista de medicos deshabilitados:");
            fread(&medicos, sizeof(Medico), 1, ptrmedicos);
            do{
                if (medicos.estado == 0){
                    printf("\n%s ", medicos.nombre);
                }
                fread(&medicos, sizeof(Medico), 1, ptrmedicos);
            } while (feof(ptrmedicos) == 0);
            fclose(ptrmedicos);
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
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
                                printf("¿Estas seguro de eliminar a este medico?");
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
                                FILE *copiaptrMedicos = fopen("registroMedicoCopia.bin", "wb");;
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
                            printf("El medico ingresado tiene pacientes registrados, por lo tanto no fue posible eliminarlo");
                        }
                        break;
                    }else{
                        fread(&copiaMedicos, sizeof(Medico), 1, ptrmedicos);
                        opcion = 0;
                        contador++;
                    }
                } while (feof(ptrmedicos) == 0);
                if (opcion == 0){
                    printf("Medico no encontrado, intentelo nuevamente");
                }
            }else{
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
        printf("\nNo hay medicos registrados por el momento, regrese cuando alla registrado a algun medico\n");
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
    printf("La cantidad de medicos son: %d\n", cont);
    for (int i = 0; i < 50; i++){
       printf("-");
    }
    printf("\n");
    printf("La cantidad de medicos inactivos son: %d\n", desh);
    for (int i = 0; i < 50; i++){
       printf("-");
    }
    printf("\n");
    printf("La cantidad de medicos activos son: %d\n", habi);
    fclose(archivo);
    printf("\n");
    continuar();
}

void continuar(){
    int conti;
    printf("Presione 1 + enter para continuar: \n\n");
    scanf("%d%*c", &conti);
}

void loginMedico(){ 
    printf("\nLogin Medico\n");
    Medico Med;
    char nombreA[100];
    char nombreL[100];
    int intentos = 0;
    do{
        printf("Ingrese su nombre:");
        scanf("%[^\n]%*c", nombreA);
        printf("Ingrese su cedula:");
        scanf("%[^\n]%*c", nombreL);
        Med = validarloginmed(nombreA,nombreL);
        if (Med.estado == -100){
            printf("\nNo hay ningun medico registrado por el momento\n");
            return;
        }
        intentos++;
        if(intentos == 3){
            printf("\nHas alcanzado el maximo de intentos\n");
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
        printf("\n¿Que accion desea realizar? (Seleccione el número de la accion)");
        printf("\n1) Modificar informacion personal");
        printf("\n2) Gestionar Pacientes");
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
                    modificarInformacionMedico(&ptrmedico);
                    break;
                case 2:
                    gestionarPaciente(ptrmedico);
                    break;
                case 3:
                    generarInformesMedico();
                    break;
                case 4:
                    printf("Cerrando sesion.\n");
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
    printf("\n              Modificar informacion personal\n");
    printf("\nNombre: %s", (*medico)->nombre);
    printf("\nCedula: %s", (*medico)->cedula);
    printf("\nDireccion: %s", (*medico)->direccion);
    printf("\nTelefono: %s", (*medico)->telefono);
    printf("\nCorreo electronico: %s", (*medico)->correo);
    printf("\nContraseña: %s", (*medico)->login);
    do{
        printf("\nSi desea cambiar su informacion personal presione 1, de lo contrario presione 2: ");
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
    printf("Si deseas omitir algun dato menos la contraseña solo preciona Enter\n");  
    if (opcion == 1){
        printf("\nIngrese el nuevo nombre completo: ");
        scanf("%[^\n]%*c", (*medico)->nombre);
        fflush(stdin);
        do{
            do{
                printf("Ingrese la nueva contraseña (Ingrese minimo 5 caracteres): ");
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
            printf("Cedula profesional (8 caracteres): ");
            scanf("%[^\n]%*c", (*medico)->cedula);
            fflush(stdin);
            longitud = strlen((*medico)->cedula);
            if (longitud != 8){
                printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
            }
        } while (longitud != 8);
        printf("Direccion: ");
        scanf("%[^\n]%*c", (*medico)->direccion);
        fflush(stdin);
        do{
            printf("Telefono(10 digitos): ");
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
        printf("Correo electronico: ");
        scanf("%[^\n]%*c", (*medico)->correo);
        fflush(stdin);
        printf("Informacion actualizada con exito\n");
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
        printf("\n¿Que accion desea realizar? (Seleccione el número de la accion)");
        printf("\n1) Registrar a un nuevo paciente");
        printf("\n2) Actualizar informacion de un paciente");
        printf("\n3) Habilitar o deshabilitar a un paciente");
        printf("\n4) Evaluar Pacientes");
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
        printf("Telefono(10 digitos): ");
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
    printf("Correo electronico: ");
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
        printf("\nNo hay pacientes registrados por el momento, regrese cuando alla registrado a algun medico\n");
        fclose(ptrpacientes);
    }else{
        fclose(ptrpacientes);
        printf("\n                     Actualizar datos\n");
        printf("\n¿De que paciente desea actualizar los datos?");
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
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
            fflush(stdin);
            scanf("%[^\n]%*c", opc);
            if (strcmp(opc, negativo) != 0){
                ptrpacientes = fopen("registroPaciente.bin", "r+b");
                fread(&pac, sizeof(Paciente), 1, ptrpacientes);
                do{
                    if ((strcmp(opc, pac.nombre) == 0) && (strcmp(medico->nombre, pac.medico) == 0)){
                        strcpy(pacienteBuscado.nombre, pac.nombre);
                        printf("\n              Modificar informacion personal\n");
                        printf("\nNombre: %s", pac.nombre);
                        printf("\nNSS: %s", pac.nss);
                        printf("\nTelefono: %s", pac.telefono);
                        printf("\nCorreo electronico: %s", pac.correo);
                        printf("\nContraseña: %s", pac.login);
                        printf("\nSi deseas omitir algun dato menos la contraseña solo preciona Enter\n");  
                            do{
                                respuesta[0] = '0';
                                printf("¿Estas seguro de actualizar la informacion de este paciente?");
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
                                            printf("Ingrese la nueva contraseña (Ingrese minimo 5 caracteres): ");
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
                                        printf("Numero de seguridad social NSS (11 caracteres): ");
                                        scanf("%[^\n]%*c", pac.nss);
                                        fflush(stdin);
                                        longitud = strlen(pac.nss);
                                        if (longitud != 11){
                                            printf("El dato ingresado no es valido, por favor intentalo nuevamente\n");
                                        }
                                    } while (longitud != 11);
                                    fflush(stdin);
                                    do{
                                        printf("Telefono(10 digitos): ");
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
                                    printf("Correo electronico: ");
                                    scanf("%[^\n]%*c", pac.correo);
                                    fflush(stdin);
                                    printf("Informacion actualizada con exito\n");
                                    printf("Informacion actualizada con exito\n");
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
                    printf("Paciente no encontrado, intentelo nuevamente");
                }
            }else{
                opcion = 1;
            }
            fclose(ptrpacientes);
        } while (opcion == 0 || opcion == 2);
        printf("Saliendo al menu Gestionar pacientes\n");
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
        printf("\nNo hay pacientes registrados por el momento, regrese cuando alla registrado a algun paciente\n");
        fclose(ptrpacientes);
    }else{
        fclose(ptrpacientes);
        printf("\n                     Habilitar o deshabilitar\n");
        printf("\n¿Que paciente desea habilitar o deshabilitar?");
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
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
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
                                printf("¿Estas seguro de inhabilitar a este paciente?");
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
        printf("Saliendo al menu Gestionar pacientes\n");
    }
}

void evaluarPaciente(Medico *medico){
    Paciente pac;
    FILE *ptrpacientes = fopen("registroPaciente.bin", "rb");
    int opcion;
    char opc[100];
    char negativo[] = ("Salir");
    if (ptrpacientes == NULL){
        printf("\nNo hay pacientes registrados por el momento, regrese cuando alla registrado a algun medico\n");
        fclose(ptrpacientes);
    }else{
        fclose(ptrpacientes);
        printf("\nEvaluar pacientes\n");
        printf("\n¿Que paciente desea evaluar?");
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
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
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
        printf("Saliendo al menu Gestionar pacientes\n");
    }
}

void evaluacion(Paciente *ptrpaciente){
    int opcion, i;
    char opc[100];
    do{
        opc[0] = '0';
        printf("\n          %s\n", ptrpaciente->nombre);
        printf("\n¿Que accion desea realizar? (Seleccione el número de la accion)");
        printf("\n1) Registrar consulta (Se registrara la fecha de hoy)");
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
        printf("\nSolo puede registrar una cita por dia\n");
    }
}

void observaciones(Paciente *ptrpaciente){
    FILE *ptrCuestionarios = fopen("registroCuestionarios.bin", "rb");
    Cuestionarios cues;
    int opcion, i, cont;
    char respuesta[100];
    char negativo[] = ("Salir");
    if (ptrCuestionarios == NULL){
        printf("\nNo hay ninguna consulta registrada, vuelva cuando registre alguna consulta.\n");
        fclose(ptrCuestionarios);
        return;
    }
    fclose(ptrCuestionarios);
    printf("\n¿A que fecha desea agregar observaciones?\n");
    do{
        cont = 1;
        printf("\nEscriba el numero de la fecha de la consulta\n");
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
        if (strcmp(ptrpaciente->nombre, cues.paciente) == 0){
            if (opcion == cont){
                fseek(ptrcues, -(long)sizeof(Cuestionarios), SEEK_CUR);
                printf("A continuacion escriba las observacioneo recomendaciones que desee agregar\n");
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
        printf("\nNo hay ninguna consulta registrada, vuelva cuando registre alguna consulta.\n");
        fclose(ptrCuestionarios);
        return;
    }
    fclose(ptrCuestionarios);
    printf("\n¿A que fecha desea agregar un cuestionario?\n");
    do{
        cont = 1;
        printf("\nEscriba el numero de la fecha de la consulta\n");
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
                    printf("Escriba el numero del cuestionario que desea agregar");
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
    Cuestionarios cues;
    Beck preg;
    int i;
    /*
    int opcion, i, cont;
    char respuesta[100];
    char negativo[] = ("Salir");
    */
    if (ptrCuestionarios == NULL){
        printf("\nNo hay ninguna consulta registrada, vuelva cuando registre alguna consulta.\n");
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
                        printf("Cuestionario de beck, puntuacion: %d/63", cues.puntuacion);
                        if (cues.puntuacion <= 13){
                            printf("\nDepresion leve");
                        }
                        if (cues.puntuacion >= 14 && cues.puntuacion <= 19){
                            printf("\nDepresion moderada");
                        }
                        if (cues.puntuacion >= 20 && cues.puntuacion <= 28){
                            printf("\nDepresion moderada-severa");
                        }
                        if (cues.puntuacion >= 29){
                            printf("\nDepresion severa");
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
        printf("\nNo hay pacientes registrados por el momento, regrese cuando alla registrado a algun paciente\n");
        fclose(ptrpaciente);
    }else{
        fclose(ptrpaciente);
        printf("\n                     Eliminar paciente\n");
        printf("\n¿Que paciente desea eliminar?");
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
            printf("\n(Si desea detener esta accion escriba 'Salir')\n");
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
                                printf("\n[%s]     1)Si    2)No     ", copiaPaciente.nombre);
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
        printf("Saliendo al menu Gestionar pacientes\n");
    }
}

//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
void generarInformesMedico(){
    printf("\nSeleccionado Generar Informes\n");
}
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder

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
            printf("\nNo hay ningun medico registrado por el momento\n");
            return;
        }
        intentos++;
        if(intentos == 3){
            printf("\nHas alcanzado el maximo de intentos\n");
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
        printf("\n¿Que accion desea realizar? (Seleccione el número de la accion)");
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
                    generarInformesPaciente();
                    break;
                case 3:
                    printf("Cerrando sesion.\n");
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
    FILE *cuestionario = fopen("registroCuestionarios.bin", "rb");
    Cuestionarios cues;
    Beck beck;
    int opcion, i, cont, respuesta, puntuacion, lecturas;
    int repeticiones[100];
    char opc[100];
    char resp[100];
    struct test{
        int test;
    }Preguntas[100];
    if (cuestionario == NULL){
        printf("\nNo hay ninguna consulta registrada, vuelva cuando registre alguna consulta.\n");
        fclose(cuestionario);
        return;
    }
    fclose(cuestionario);
    do{
        printf("\nSeleccione el numero del cuestionario que desea responder.");
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
            printf("\nNo tienes ningun cuestionario asignado por el momento\n");
            return;
        }
        printf("\n");
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
                    strcpy(beck.paciete, ptrpac->nombre);
                    puntuacion = 0;
                    printf("\nIngrese el numero de la respuesta que mejor describa su situacion");
                    do{
                        printf("\n1) Trizteza");
                        strcpy(beck.pregunta[0].pregunta, "1) Trizteza");
                        printf("\n1) No me siento triste");
                        printf("\n2) Me siento triste gran parte del tiempo");
                        printf("\n3) Me siento triste todo el tiempo");
                        printf("\n4) Me siento tan triste o soy tan infeliz que no puedo soportarlo\n");
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
                        printf("\n2) Pesimismo");
                        strcpy(beck.pregunta[1].pregunta, "2) Pesimismo");
                        printf("\n1) No estoy desalentado respecto del mi futuro");
                        printf("\n2) Me siento más desalentado respecto de mi futuro que lo que solía estarlo");
                        printf("\n3) No espero que las cosas funcionen para mi");
                        printf("\n4) Siento que no hay esperanza para mi futuro y que sólo puede empeorar\n");
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
                                    strcpy(beck.respuesta[1].respuesta, "No estoy desalentado respecto del mi futuro");
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
                        printf("\n3) Fracaso");
                        strcpy(beck.pregunta[2].pregunta, "3) Fracaso");
                        printf("\n1) No me siento como un fracasado");
                        printf("\n2) He fracasado más de lo que hubiera debido");
                        printf("\n3) Cuando miro hacia atrás, veo muchos fracasos");
                        printf("\n4) Siento que como persona soy un fracaso total\n");
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
                        printf("\n4) Perdida de placer");
                        strcpy(beck.pregunta[3].pregunta, "4) Perdida de placer");
                        printf("\n1) Obtengo tanto placer como siempre por las cosas de las que disfruto");
                        printf("\n2) No disfruto tanto de las cosas como solía hacerlo");
                        printf("\n3) Obtengo muy poco placer de las cosas que solía disfrutar");
                        printf("\n4) No puedo obtener ningún placer de las cosas de las que solía disfrutar\n");
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
                        printf("\n5) Sentimientos de culpa");
                        strcpy(beck.pregunta[4].pregunta, "5) Sentimientos de culpa");
                        printf("\n1) No me siento particularmente culpable");
                        printf("\n2) Me siento culpable respecto de varias cosas que he hecho o que debería haber hecho");
                        printf("\n3) Me siento bastante culpable la mayor parte del tiempo");
                        printf("\n4) Me siento culpable todo el tiempo\n");
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
                        printf("\n6) Sentimientos de castigo");
                        strcpy(beck.pregunta[5].pregunta, "6) Sentimientos de castigo");
                        printf("\n1) No siento que este siendo castigado");
                        printf("\n2) Siento que tal vez pueda ser castigado");
                        printf("\n3) Espero ser castigado");
                        printf("\n4) Siento que estoy siendo castigado\n");
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
                        printf("\n7) Dsiconformidad con uno mismo");
                        strcpy(beck.pregunta[6].pregunta, "7) Disconformidad con uno mismo");
                        printf("\n1) Siento acerca de mi lo mismo que siempre");
                        printf("\n2) He perdido la confianza en mí mismo");
                        printf("\n3) Estoy decepcionado conmigo mismo");
                        printf("\n4) No me gusto a mí mismo\n");
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
                        printf("\n8) Autocritica");
                        strcpy(beck.pregunta[7].pregunta, "8) Autocritica");
                        printf("\n1) No me critico ni me culpo más de lo habitual");
                        printf("\n2) Estoy más crítico conmigo mismo de lo que solía estarlo");
                        printf("\n3) Me critico a mí mismo por todos mis errores");
                        printf("\n4) Me culpo a mí mismo por todo lo malo que sucede\n");
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
                        printf("\n9) Pensamientos o deseos suicidas");
                        strcpy(beck.pregunta[8].pregunta, "9) Pensamientos o deseos suicidas");
                        printf("\n1) No tengo ningún pensamiento de matarme");
                        printf("\n2) He tenido pensamientos de matarme, pero no lo haría");
                        printf("\n3) Querría matarme");
                        printf("\n4) Me mataría si tuviera la oportunidad de hacerlo\n");
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
                        printf("\n10) Llanto");
                        strcpy(beck.pregunta[9].pregunta, "10) Lanto");
                        printf("\n1) No lloro más de lo que solía hacerlo");
                        printf("\n2) Lloro más de lo que solía hacerlo");
                        printf("\n3) Lloro por cualquier pequeñez");
                        printf("\n4) Siento ganas de llorar pero no puedo\n");
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
                        printf("\n11) Agitacion");
                        strcpy(beck.pregunta[10].pregunta, "11) Agitacion");
                        printf("\n1) No estoy más inquieto o tenso que lo habitual");
                        printf("\n2) Me siento más inquieto o tenso que lo habitual");
                        printf("\n3) Estoy tan inquieto o agitado que me es difícil quedarme quieto");
                        printf("\n4) Estoy tan inquieto o agitado que tengo que estar siempre en movimiento o haciendo algo\n");
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
                        printf("\n12) Perdida de interes");
                        strcpy(beck.pregunta[11].pregunta, "12) Perdida de interes");
                        printf("\n1) No he perdido el interés en otras actividades o personas");
                        printf("\n2) Estoy menos interesado que antes en otras personas o cosas");
                        printf("\n3) He perdido casi todo el interés en otras personas o cosas");
                        printf("\n4) Me es difícil interesarme por algo\n");
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
                        printf("\n13) Indecision");
                        strcpy(beck.pregunta[12].pregunta, "13) Indecision");
                        printf("\n1) Tomo mis propias decisiones tan bien como siempre");
                        printf("\n2) Me resulta más difícil que de costumbre tomar decisiones");
                        printf("\n3) Encuentro mucha más dificultad que antes para tomar decisiones");
                        printf("\n4) Tengo problemas para tomar cualquier decisión\n");
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
                        printf("\n14) Desvalorizacion");
                        strcpy(beck.pregunta[13].pregunta, "14) Desvalorizacion");
                        printf("\n1) No siento que yo no sea valioso");
                        printf("\n2) No me considero a mi mismo tan valioso y útil como solía considerarme");
                        printf("\n3) Me siento menos valioso cuando me comparo con otros");
                        printf("\n4) Siento que no valgo nada\n");
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
                        printf("\n15) Perdida de energia");
                        strcpy(beck.pregunta[14].pregunta, "15) Perdida de energia");
                        printf("\n1) Tengo tanta energía como siempre");
                        printf("\n2) Tengo menos energía que la que solía tener");
                        printf("\n3) No tengo suficiente energía para hacer demasiado");
                        printf("\n4) No tengo energía suficiente para hacer nada\n");
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
                        printf("\n16) Cambios en los habitos de sueño");
                        strcpy(beck.pregunta[15].pregunta, "16) Cambios en los habitos de sueño");
                        printf("\n1) No he experimentado ningún cambio en mis hábitos de sueño");
                        printf("\n2) Duermo un poco menos que lo habitual");
                        printf("\n3) Duermo mucho menos que lo habitual");
                        printf("\n4) Me despierto 1-2 horas más temprano y no puedo volver a dormirme\n");
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
                        printf("\n17) Irritabilidad");
                        strcpy(beck.pregunta[16].pregunta, "17) Irritabilidad");
                        printf("\n1) No estoy tan irritable que lo habitual");
                        printf("\n2) Estoy más irritable que lo habitual");
                        printf("\n3) Estoy mucho más irritable que lo habitual");
                        printf("\n4) Estoy irritable todo el tiempo\n");
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
                        printf("\n18) Cambios en el apetito");
                        strcpy(beck.pregunta[17].pregunta, "18) Cambios en el apetito");
                        printf("\n1) No he experimentado ningún cambio en mi apetito");
                        printf("\n2) Mi apetito es un poco menor que lo habitual");
                        printf("\n3) Mi apetito es mucho menor que antes");
                        printf("\n4) No tengo apetito en absoluto\n");
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
                        printf("\n19) Dificultad de concentracion");
                        strcpy(beck.pregunta[18].pregunta, "19) Dificultad de concentracion");
                        printf("\n1) Puedo concentrarme tan bien como siempre");
                        printf("\n2) No puedo concentrarme tan bien como habitualmente");
                        printf("\n3) Me es difícil mantener la mente en algo por mucho tiempo");
                        printf("\n4) Encuentro que no puedo concentrarme en nada\n");
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
                        printf("\n20) Cansancio o fatiga");
                        strcpy(beck.pregunta[19].pregunta, "20) Cansancio o fatiga");
                        printf("\n1) No estoy más cansado o fatigado que lo habitual");
                        printf("\n2) Me fatigo o me canso más fácilmente que lo habitual");
                        printf("\n3) Estoy demasiado fatigado o cansado para hacer muchas de las cosas que solía hacer");
                        printf("\n4) Estoy demasiado fatigado o cansado para hacer la mayoría de las cosas que solía hacer\n");
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
                        printf("\n21) Perdida de interes en el sexo");
                        strcpy(beck.pregunta[20].pregunta, "21) Perdida de interes en el sexo");
                        printf("\n1) No he notado ningún cambio reciente en mi interés por el sexo");
                        printf("\n2) Estoy menos interesado en el sexo de lo que solía estarlo");
                        printf("\n3) Estoy mucho menos interesado en el sexo");
                        printf("\n4) He perdido completamente el interés en el sexo\n");
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
                    printf("MDI");
                    break;
                case 3:
                    printf("Zung");
                    break;
                case 4:
                    printf("PHQ-9");
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

//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
void generarInformesPaciente(){
    printf("\nSeleccionado Visualizar datos de las consultas\n");
}
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder
//Eder