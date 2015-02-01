<?php
    require("../index.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        
        if (empty($_POST["username"])){
            
            apologize("You must provide your username");
        
        }else if (empty($_POST["password"])){
            
            apologize("You must provide your password");
        }
        
        $rows = query ("SELECT * FROM users WHERE username = ?", $_POST["username"]);
        
        if(count($rows) == 1){
            $row = $rows[0];
            // compare hash of user's input against hash that's in database
            if (crypt($_POST["password"], $row["hash"]) == $row["hash"])
            {
                // remember that user's now logged in by storing user's ID in session
                $_SESSION["id"] = $row["id"];
                // redirect to portfolio
                redirect("/");
            }
        }
        
        apologize("Invalid username and/or password.");
        
    }else{
        require("../index.php");
    }
    

?>