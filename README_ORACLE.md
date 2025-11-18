# Guide de Connexion à Oracle

## État Actuel

Votre projet est actuellement connecté à **SQLite** (base de données locale). 

## Comment Connecter à Oracle

### Option 1 : Via l'Interface Graphique

1. **Lancez l'application**
2. **Allez dans le menu** : `Base de Données` → `Configurer la connexion...`
3. **Sélectionnez "Oracle"** dans le menu déroulant
4. **Remplissez les paramètres** :
   - **Hôte** : `localhost` (ou l'adresse IP de votre serveur Oracle)
   - **Port** : `1521` (port par défaut d'Oracle)
   - **Base de données (SID)** : `XE` (pour Oracle Express) ou `ORCL` (pour Oracle Standard)
   - **Utilisateur** : Votre nom d'utilisateur Oracle (ex: `system`, `hr`)
   - **Mot de passe** : Votre mot de passe Oracle
5. **Cliquez sur "Tester la Connexion"** pour vérifier
6. **Cliquez sur "OK"** pour établir la connexion

### Option 2 : Prérequis pour Oracle

#### 1. Installer Oracle Instant Client

1. Téléchargez **Oracle Instant Client** depuis le site Oracle
2. Extrayez-le dans un dossier (ex: `C:\oracle\instantclient_21_8`)
3. Ajoutez le chemin au **PATH** de Windows :
   - Panneau de configuration → Système → Variables d'environnement
   - Ajoutez `C:\oracle\instantclient_21_8` à la variable PATH

#### 2. Configurer Qt pour Oracle

Le driver **QOCI** (Qt Oracle Call Interface) doit être disponible. Il est généralement inclus avec Qt si Oracle Client est installé.

#### 3. Vérifier la Connexion Oracle

Assurez-vous que :
- Oracle Database est **démarré**
- Le **listener Oracle** est actif
- Vous pouvez vous connecter avec **SQL Developer** ou **sqlplus**

### Paramètres Typiques

#### Oracle Express Edition (XE)
```
Hôte: localhost
Port: 1521
SID: XE
Utilisateur: system
Mot de passe: (celui que vous avez défini lors de l'installation)
```

#### Oracle Standard Edition
```
Hôte: localhost (ou adresse IP)
Port: 1521
SID: ORCL (ou votre SID)
Utilisateur: system
Mot de passe: (votre mot de passe)
```

### Création Automatique des Tables

Lors de la première connexion à Oracle, l'application créera automatiquement :
- Les **séquences** pour les IDs auto-incrémentés
- Les **tables** : `abonnes`, `activites`, `inscriptions`
- Les **triggers** pour l'auto-incrémentation
- Les **contraintes** de clés étrangères

### Différences SQLite vs Oracle

| Fonctionnalité | SQLite | Oracle |
|---------------|--------|--------|
| Type de données dates | TEXT | DATE |
| Auto-incrémentation | AUTOINCREMENT | Séquences + Triggers |
| Format dates | 'YYYY-MM-DD' | TO_DATE('YYYY-MM-DD') |
| Types numériques | INTEGER, REAL | NUMBER |

### Dépannage

#### Erreur : "Driver Oracle (QOCI) non disponible"
- Installez Oracle Instant Client
- Vérifiez que le chemin est dans PATH
- Redémarrez Qt Creator

#### Erreur : "Échec de la connexion"
- Vérifiez que Oracle est démarré
- Vérifiez le listener : `lsnrctl status`
- Testez avec SQL Developer d'abord
- Vérifiez le SID/Service Name

#### Erreur : "ORA-12541: TNS:no listener"
- Démarrez le listener Oracle : `lsnrctl start`
- Vérifiez le fichier `listener.ora`

### Retour à SQLite

Pour revenir à SQLite :
1. Menu `Base de Données` → `Configurer la connexion...`
2. Sélectionnez "SQLite (Local)"
3. Cliquez sur "OK"

La base SQLite sera créée automatiquement dans le dossier AppData.

