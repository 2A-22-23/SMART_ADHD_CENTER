#include "user.h"
#include "QSqlQuery"
#include "QDebug"
#include <QObject>
#include <QMessageBox>
#include <QAxObject>

User::User()
{
id=0;
nom="";
prenom="";
cin="";
email="";
role="";
mdp="";
}




User::User(int id,QString nom,QString prenom,QString cin,QString email,QString role,QString mdp)
{this->id=id;this->nom=nom;this->prenom=prenom; this->cin=cin;this->email=email;this->role=role;this->mdp=mdp;}
int User::getid(){return id;}
QString User::getnom(){return nom;}
QString User::getprenom(){return prenom;}
QString User::getcin(){return cin;}
QString User::getemail(){return email;}
QString User::getrole(){return role;}
QString User::getmdp(){return mdp;}
void User::setid(int id){this->id=id;}
void User::setnom(QString nom){this->nom=nom;}
void User::setprenom(QString prenom){this->prenom=prenom;}
void User::setcin(QString cin){this->cin=cin;}
void User::setemail(QString email){this->email=email;}
void User::setrole(QString role){this->role=role;}
void User::setmdp(QString mdp){this->mdp=mdp;}





bool User::ajouter(){


    QSqlQuery query;
    QString id_string=QString::number(id);
          query.prepare("INSERT INTO ADMINS (id, nom, prenom,cin,email,role,mdp) "
                        "VALUES (:id, :nom, :prenom, :cin, :email, :role, :mdp)");
          query.bindValue(0,id_string );
          query.bindValue(1, nom);
          query.bindValue(2, prenom);
          query.bindValue(3, cin);
          query.bindValue(4, email);
          query.bindValue(5, role);
          query.bindValue(6, mdp);

          return query.exec();
}




QSqlQueryModel* User::afficher()
{
 QSqlQueryModel *model = new QSqlQueryModel;
 model->setQuery("SELECT * FROM ADMINS");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("email"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("role"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("mdp"));
return model;


}






bool User::supprimer(int id)
{
 QSqlQuery query;
 query.prepare("Delete from ADMINS where id=:id ");
 query.bindValue(0,id );
 return query.exec();

}

bool User::modifier(int id)
{

    QSqlQuery query;
    //QString id_string=QString::number(id);

    //

   query.prepare("UPDATE ADMINS SET nom=:nom,prenom=:prenom,cin=:cin,email=:email,role=:role,mdp=:mdp WHERE id=:id");

    //
   query.bindValue(6,id);
   query.bindValue(0, nom);
   query.bindValue(1, prenom);
   query.bindValue(2, cin);
   query.bindValue(3, email);
   query.bindValue(4, role);
   query.bindValue(5, mdp);


    return query.exec();
}
bool User::recherche(int a){
QSqlQuery query;
QString id1=QString::number(a);
query.prepare("select * from ADMINS where id=:id ");
query.bindValue(":id",id1);
query.exec();
    if (query.next()) {
        int compter= query.value(0).toInt();
        return (compter >0); // Utilisateur trouvé
    } else {
        return false; // Utilisateur non trouvé
    }
}


QSqlQueryModel * User::afficher_search_result(QString ch)
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from ADMINS where id LIKE '%"+ch+"%' ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("role"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("mdp"));
return model;
}


QSqlQueryModel * User::afficher_id_decroissant()
{
  QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from ADMINS order by id DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("role"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("mdp"));
return model;

}
QSqlQueryModel * User::afficher_id_croissant()
{
  QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from ADMINS order by id ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("role"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("mdp"));
return model;

}

bool User::comparerEmailMotDePasse(const QString& email, const QString& motDePasse) {
     QSqlQuery query;
     query.prepare("SELECT email FROM ADMINS WHERE email = ? AND mdp = ?"); // Remplacez "utilisateurs" par le nom de votre propre table d'utilisateurs
         query.bindValue(0, email);
         query.bindValue(1, motDePasse);


        if (!query.exec()) {
                 qWarning() << "Erreur lors de l'exécution de la requête SQL:"/* << query.lastError().text()*/;
                 return false;
             }

             // Vérifier si la requête a renvoyé un résultat
             if (query.next()) {
                 qDebug() << "Email et mot de passe valides.";
                 QMessageBox::information(nullptr, QObject::tr("Add"),
                             QObject::tr("Email et mot de passe valides.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
                 return true;
             } else {
                 qDebug() << "Email ou mot de passe invalides.";
                 QMessageBox::information(nullptr, QObject::tr("Add"),
                             QObject::tr("Email ou mot de passe invalides..\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
                 return false;
             }


}



void User::envoyer_mail(QString destination) {
     qDebug() << "test test";
     QAxObject* outlook = new QAxObject("Outlook.Application");
     QSqlQuery query;
     QString mdp;
     query.prepare("SELECT mdp FROM ADMINS WHERE email =:x ");

     query.bindValue(":x", destination);
     query.exec();

     while (query.next())
          {
             mdp = query.value(0).toString();
         }

     if (!outlook->isNull()) {
         QAxObject* mail = outlook->querySubObject("CreateItem(int)", 0);
         mail->setProperty("To", destination);
         mail->setProperty("Subject", "mot de passe oublier");
         mail->setProperty("Body", "Bonjour M./Mme. "",\n\nVoici votre mot de passe :\n"+mdp+"\n");
         mail->dynamicCall("Send()");
     }

 }









