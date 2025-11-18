# Guide de Configuration du Projet

## Problème résolu : Boutons de compilation/exécution manquants

Le projet a été corrigé pour fonctionner même si Qt Charts n'est pas installé.

## Étapes pour restaurer les boutons dans Qt Creator

### 1. Nettoyer le projet
- Dans Qt Creator, allez dans **Build** → **Clean All**
- Supprimez le dossier `build` si nécessaire

### 2. Reconfigurer CMake
- Allez dans **Build** → **Run CMake**
- Ou cliquez sur **Projects** (icône en bas à gauche)
- Sélectionnez votre kit Qt (ex: Desktop Qt 6.10.0 MinGW 64-bit)
- Cliquez sur **Configure Project**

### 3. Vérifier la configuration
- Le projet devrait maintenant se configurer correctement
- Les boutons de compilation (🔨) et d'exécution (▶) devraient réapparaître

### 4. Compiler
- Cliquez sur le bouton **Build** (🔨) ou appuyez sur **Ctrl+B**
- Le projet devrait compiler sans erreur

### 5. Exécuter
- Cliquez sur le bouton **Run** (▶) ou appuyez sur **Ctrl+R**

## Notes importantes

### Qt Charts (Optionnel)
- Si Qt Charts n'est **pas installé** : Le projet compilera et fonctionnera, mais les graphiques seront remplacés par un affichage textuel des statistiques
- Si Qt Charts **est installé** : Les graphiques seront automatiquement activés

### Pour installer Qt Charts (optionnel)
1. Ouvrez **Qt Maintenance Tool**
2. Sélectionnez votre installation Qt
3. Ajoutez le composant **Qt Charts** dans les modules additionnels
4. Réconfigurez le projet après l'installation

## Dépendances requises
- Qt 6.5 ou supérieur
- Qt Core
- Qt Widgets
- Qt Sql

## Dépendances optionnelles
- Qt Charts (pour les graphiques)

## Structure du projet
```
smart-summer-club/
├── main.cpp                 # Point d'entrée
├── mainwindow.h/cpp/ui      # Fenêtre principale
├── inscription.h/cpp        # Classe Inscription
├── databasemanager.h/cpp    # Gestion de la base de données
├── CMakeLists.txt           # Configuration CMake
└── build/                   # Dossier de compilation (généré)
```

## Fonctionnalités
✅ Recherche en temps réel
✅ Tri par plusieurs critères
✅ Export PDF avec QR code
✅ Statistiques (graphiques si Qt Charts disponible, sinon texte)
✅ Génération de QR code

