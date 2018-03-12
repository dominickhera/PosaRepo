// Put all onload AJAX calls here, and event listeners

$(document).ready(function() {
    // On page-load AJAX Example
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/someendpoint',   //The server endpoint we are connecting to
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */


            //We write the object to the console to show that the request was successful
            console.log(data); 
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });

    // Event listener form replacement example, building a Single-Page-App, no redirects if possible
    $('uploadForm').submit(function(e){
        e.preventDefault();
        $.ajax({});
        console.log("hi");
    });



    var acc = document.getElementsByClassName("accordion");
    var i;

    for (i = 0; i < acc.length; i++) {
      acc[i].addEventListener("click", function() {
        this.classList.toggle("active");
        var panel = this.nextElementSibling;
        if (panel.style.maxHeight){
          panel.style.maxHeight = null;

        } else {
          panel.style.maxHeight = panel.scrollHeight + "px";
          console.log(panel.scrollHeight)
        } 
      });
    }

    var uploadModal = document.getElementById('uploadModal');
    var uploadBtn = document.getElementById("uploadFile");
    var uploadSpan = document.getElementById("uploadClose");
    var uploadSubmit = document.getElementById("uploadSubmit");
    uploadBtn.onclick = function() {
        uploadModal.style.display = "block";
    }

    uploadSpan.onclick = function() {
        uploadModal.style.display = "none";
    }

    window.onclick = function(event) {
        if (event.target == uploadModal) {
            uploadModal.style.display = "none";
        }
        
    }

    // uploadSubmit.onclick = function(event) {
    //     event.preventDefault();
    // }
    // app.use(fileUpload());
    // app.post('/uploads', function(req, res) {
    //     if(!req.files)
    //     {
    //         return res.status(400).send('Error uploading file');
    //     }

    //     let gedcomFile = req.files.gedcomFile;

    //     gedcomFile.mv('/uploads', function(err) {
    //         if(err)
    //         {
    //             return res.status(500).send(err);
    //         }

    //         res.send('File Uploaded');
    //     });
    // });

    var createModal = document.getElementById('createModal');
    var createBtn = document.getElementById("createSimpleGedcom");
    var createSpan = document.getElementById("createClose");
    createBtn.onclick = function() {
        createModal.style.display = "block";
    }

    createSpan.onclick = function() {
        createModal.style.display = "none";
    }

    window.onclick = function(event) {
        if (event.target == createModal) {
            createModal.style.display = "none";
        }
    }

    var addModal = document.getElementById('addModal');
    var addBtn = document.getElementById("addIndividual");
    var addSpan = document.getElementById("addClose");
    addBtn.onclick = function() {
        addModal.style.display = "block";
    }

    addSpan.onclick = function() {
        addModal.style.display = "none";
    }

    window.onclick = function(event) {
        if (event.target == addModal) {
            addModal.style.display = "none";
        }
    }


    var getModal = document.getElementById('getModal');
    var getBtn = document.getElementById("getDescendants");
    var getSpan = document.getElementById("getClose");
    getBtn.onclick = function() {
        getModal.style.display = "block";
    }

    getSpan.onclick = function() {
        getModal.style.display = "none";
    }

    window.onclick = function(event) {
        if (event.target == getModal) {
            getModal.style.display = "none";
        }
    }

});
