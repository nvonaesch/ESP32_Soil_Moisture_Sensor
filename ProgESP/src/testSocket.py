import socket

IP = '192.168.1.83'  # A remplacer par l'adresse renvoyée par bluetooth
PORT = 9090  

def request_sensor_data():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((IP, PORT))
            print(f"Connecte {IP}:{PORT}")

            s.sendall(b'GET_SENSOR_VALUE')

            data = s.recv(1024)  
            print("Valeur capteur :", int.from_bytes(data))

    except ConnectionRefusedError:
        print("Connexion refusee.")
    except Exception as e:
        print(f"Erreur : {e}")

if __name__ == "__main__":
    request_sensor_data()
