
.
./main.c
src (
./tokanisation
./parsing
./cleaning
./signal
./pipe
./built_ins
)

Le parsing :
On récupère la commande de l'utilisateur
On sépare les éléments de la commande (commande, arguments, redirections, pipes, variables d'environnement, etc)
On traite les erreurs de parsing (gestion des quotes, des espaces, des caractères spéciaux, etc)
On stocke les éléments de la commande dans une structure de données avec un espace différent pour chaque type d'élément
Et chaque nouvelle commande a une nouvelle structure de données (ex : ""ls -l | grep test"" a deux structures de données)
On gère les expansions de commandes (ex: echo $PATH)

Fonction	Avantage de la liste chaînée
Lexing	Pas besoin de realloc ou deviner la taille
Parsing	Lecture séquentielle, facile à séparer les blocs
Pipe	Tu peux créer une commande par tronçon entre les pipes
Redirection	Tu sautes 2 tokens (>, puis file.txt) facilement
Expansion	Tu modifies le value du token directement