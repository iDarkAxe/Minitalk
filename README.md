# Simple Communication Protocol using Unix Signals #
2 Binaries, `server` for listening all messages and `client` to send messages.

# How does it work #
Each character of the string will be cut in 8 pieces (8 bits) and send separetely using `kill` function to send Unix Signals.
`SIGUSR1` is used for 1 (ones) and `SIGUSR2` for 0 (zeros).

There is near 0 down time in the client as it's not using `sleep()` or `usleep()`.
When 8 bits are send, the server concatenes it into a string and waits for the end character to print the string.

The server send an ACK (acknowledgement) signal (`SIGUSR1`) to client when a bit is received.
If the client receives nothing, it will end itself after a fixed time (TIMEOUT defined in `ft_client.h`).
When 8 bits are received by `server`, the `server` sends a `SIGUSR2` signal to say "wait for my processing time".

# How to use `server` #
Just start it using :
```sh
./server
```
It will wait for signals indefinitely and should never end by itself.
It's PID (Process Identifier) should be written in the terminal.

Do Ctrl+C or send a UNIX Signal (any except `SIGUSR1` and `SIGUSR2`) to terminate the program. 

# How to use `client` #
Just start it using :
```sh
./client <PID> <string>
```
PID is the server PID to send the string.

String can be void so just a '\0' should be send.
String can be used from a shell evaluation like :
```sh
./client <PID> $(cat <path_to/some file>)
```

For the bonus version, `<PID>` is not required (it will find the PID of server by itself).

---

# Simple protocole de Communication utilisant les signaux UNIX #
2 exécutables, `server` pour l'écoute et `client` pour envoyer des messages.

# Comment ça marche ? #
Chaque charactère de la chaîne va être découpé en 8 parties (8 bits) et envoyés séparément en utilisant la fonction `kill`.
`SIGUSR1` pour les 1 (uns) et `SIGUSR2` pour les 0 (zéros).

Il n'y a quasiment pas de délai car le client n'utilise pas de les fonctions d'attente `sleep()` ou `usleep()`.
Quand 8 bits sont envoyés, le serveur concatène le charactère formé à une chaîne en attente du charactère de fin de chaine, et ensuite l'imprime dans la sortie standard.

Le serveur envoie un signal ACK (acquittement) (`SIGUSR1`) au client lorsqu'un bit est reçu.
Si le client ne reçoit pas de réponse dans les temps, il va s'arrêter de lui même après un temps (défini dans `ft_client.h`).
Lorsque 8 bits sont reçus par le `serveur`, le `serveur` envoie un signal `SIGUSR2` pour signifier au `client` "attends que jinisse mes calculs".

# Comment utiliser `server` ? #
Lancer le programme comme ceci :
```sh
./server
```
Le programme va attendre tout les signaux et ne devrait jamais se fermer tout seul.
Son PID (Identifiant de Processus) devrait s'afficher au démarrage dans le terminal.

Faire Ctrl+C ou envoyer un signal UNIX (n'importe lequel à part `SIGUSR1` et `SIGUSR2`) devraient fermer le programme.

# Comment utiliser `client` ? #
Lancer le programme comme ceci :
```sh
./client <PID> <string>
```
PID est le PID du serveur ciblé vers lequel on veut envoyer la chaîne de charactère.

String peut être vide, donc seulement un charactère de fin de chaîne sera envoyé.
String peut être évalué par le shell comme suivant :
```sh
./client <PID> $(cat <path_to/some file>)
```

Pour la versin bonus, `<PID>` n'est pas requis (le client trouvera tout seul le premier PID du serveur).
