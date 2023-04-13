# Gladiators
Basic Gladiator fight in Unreal Engine

ENEMY : Class Enemy standard, Il peut attaquer/ prendre des dégâts ou mourir.
Le hammer est attachée au départ

ENEMYAICONTROLLER: Permet de link avec le bt de chaque enemy, il set les valeurs.

AIMANAGER : Permet de gérer tous les ennemis. il peut aussi les remove. Il contient les info pour le “Super ai manager” qui a son propre bt.

ENEMYATTACK : Permet pour que l'ennemi attaque. 

FINDPOINTAROUNDPLAYER : Trouve un point autour du joueur pour se repositionner. Il represent un service pour bt enemy.

FINDPLAYERLOCATION: Trouve le position du joueur.

CHASEPLAYER : Permet de transmettre au Super ai que l'ennemi a réussi son attaque.

SELECTRANDOMENEMY : Permet le Super Ai de selectionner un ennemi au random pour attacker le joueur.

BLACKBOARDKEYS: Représente les keys des 2 blackboards qu’on a besoin.

DAMAGECOMPONENT: Component qui s’attache aux enemies et joueur, permet de recevoir des dégâts.

GAMEOVER: Permet d’afficher les ecrans de gameover et win.

GAMESTATEMANAGER: Permet de changer le gamestate, soit pour win or lose.

HAMMERHITCOLLISION: Permet de détecter quand on attaque, si le marteau touche quelqu'un d'autre. Si oui il applique des damages.

GLADIATORSCHARACTER: Représente le personnage, il peut bouger, regarder autour de lui. 

PLAYERHUD: représente le HUD du joueur, ce qui est la barre d’HP. 

BEHAVIORTREES:

ENEMY : Soit il est notifie par le super ai d’attaquer le joueur, la il cherche la position du joueur, avance vers lui et l’attaque. Ou Il trouve un point autour du joueur pour roamer autour de lui.

AIManager: le Super AI, il check si un ennemi attaque, si non il choisit un pour attaquer.

Images : 

![1](https://user-images.githubusercontent.com/99834983/231850954-0365ad77-6bf5-4e17-b47d-7f7c4a42d05d.PNG)

![2](https://user-images.githubusercontent.com/99834983/231850992-5731c3b3-b36f-43c9-aeb6-f8883a5385d8.PNG)

![3](https://user-images.githubusercontent.com/99834983/231851012-d5b6d4b3-6a29-4a2b-bf57-c20c4987d272.PNG)
