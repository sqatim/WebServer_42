<?php
/*---------------------------------------------------------------*/
/*
    Titre : Affiche et compte le nombre de checkbox                                                                       
                                                                                                                          
    URL   : https://phpsources.net/code_s.php?id=299
    Auteur           : david96                                                                                            
    Date édition     : 05 Sept 2007                                                                                       
    Date mise à jour : 28 Aout 2019                                                                                      
    Rapport de la maj:                                                                                                    
    - fonctionnement du code vérifié                                                                                    
*/
/*---------------------------------------------------------------*/?>
    <html>
    <head><title>Formulaire exemple</title></head>
    <body>
    <form action="" method="post">
    Element-1 <input type="checkbox" name="checkbox_id[]" value="Element-1"
 /><br />
    Element-2 <input type="checkbox" name="checkbox_id[]" value="Element-2"
 /><br />
    <!-- etc... //-->
    <input type="submit" />
    </form>
<?php
    if(isset($_POST['checkbox_id']))
    {
      // On assigne notre variable $_POST['checkbox_id']
      $nombre=$_POST['checkbox_id'];
      
      /* On crée une variable qui comptera le nombre de
      checkbox choisis grâce à la fonction count() */
      $total=count($nombre);
      
      // On affiche le résultat
      $s =($total<=1) ? "" : "s"; // astuce pour le singulier ou le pluriel
      echo "Vous avez sélectionné <strong>".$total."</strong> critère".$s;
      
      /* Une petite boucle pour afficher les valeurs qu'on 
          a sélectionné dans notre formulaire */
      for( $i=0; $i<$total; $i++ )
      {
        echo "<br />",$i+1,"e choix : ".$nombre[$i];
      }
    }
    else
    {
      echo "Thanks for ur time.";
    }
?>
    </body>
    </html>
