#include "CommandNew.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

void CommandNew::exec( Data& data, UserInterface& ui ) 
{ 
   bool response= true;
   if ( &data.getCurrentFile() ) {
      if ( !data.getCurrentFile().isSaved() )
         response= ui.confirmOperation( "Existe um arquivo aberto e ele n�o est� salvo, deseja continuar mesmo assim?" );
   }
   
   if (response)
      ui.showPopupNewFile();
}