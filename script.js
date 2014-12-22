// Function to control relays. 
function buttonClick(clicked_id){

    if (clicked_id == "1"){
        $.get( "curl.php", {
        pin: "7", state: "0"
    } );  
    } 

    if (clicked_id == "2"){
        $.get( "curl.php", {
        pin: "6", state: "0"} );  
    } 


}