# Devoir 2 - Sauvegarde de matrice dans un fichier

### Ecrire un programme qui permet d'enregistrer et d'afficher une matrice carrée au format binaire et texte.   
### Le programme prend en argument sur la ligne de commande les options suivantes :
-c   // permet de demander la creation d'une matrice aléatoire 
-a  // pour induquer au programme d'afficher le contenu du fichier 
-d entier // spécifie la dimension de la matrice exemple -d 10 permet d'indiquer que c'est une matrice 10x10  
-b // indique que c'est en mode binaire (mode par defaut)
-t // indique le format du fichier est en mode texte 
-f nomfichier // specifie le nom du fichier 
Les usages possibles du programmes ./matrix -c -d 10 -f fichiermatrice.bin
./matrix -c -d 10 -f fichiermatrice.bin -t
./matrix -a -d 10 -f fichiermatrice.bin -t
