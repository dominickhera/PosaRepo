// Put all onload AJAX calls here, and event listeners
// const fs = require('fs');
$(document).ready(function() {
    // On page-load AJAX Example
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/uploads/',   //The server endpoint we are connecting to
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
            // console.log("hi");
            var uploadFileArrayLength = data.fileArrayList.length;
            console.log("length is" + uploadFileArrayLength);
            // var fileTableArray = $('$fileTable');
            var fileTableArray = document.getElementById('fileTable');
            var gedcomViewerOptions = document.getElementById('gedcomViewFileList');
            var addIndFileList = document.getElementById('addIndFileList');
            var gedcomViewTableArray = document.getElementById('gedcomTable');

            for (i = 0; i < uploadFileArrayLength; i++) { 
               // console.log(data.fileIndList.length + "at i value:" + i);
                $( "<div>" )
                .append(data.fileArrayList[i] + "has successfully been loaded in.\n" )
                .appendTo( "#statusBox" );


                let fileInfo = JSON.parse(data.fileInfoList[i]);
                // console.log(fileInfo.source);
                var newRow = fileTableArray.insertRow(i+1);
                var cellOne = newRow.insertCell(0);
                var cellTwo = newRow.insertCell(1);
                var cellThree = newRow.insertCell(2);
                var cellFour = newRow.insertCell(3);
                var cellFive= newRow.insertCell(4);
                var cellSix = newRow.insertCell(5);
                var cellSeven = newRow.insertCell(6);
                var cellEight = newRow.insertCell(7);
                // testCell.innerHTML("hello");
                // cellOne.innerHTML += ('<a href="/uploads/simpleValid.ged">simpleValid.ged</a>');
                cellOne.innerHTML += ( '<a href="/uploads/' + data.fileArrayList[i] + '">' + data.fileArrayList[i] + '</a>');
                cellTwo.innerHTML += (fileInfo.source);
                cellThree.innerHTML += (fileInfo.version);
                cellFour.innerHTML += (fileInfo.encoding);
                cellFive.innerHTML += (fileInfo.submitterName);
                cellSix.innerHTML += (fileInfo.submitterAddress);
                cellSeven.innerHTML += (fileInfo.totalIndividuals);
                cellEight.innerHTML += (fileInfo.totalFamilies);
                // gedcomViewerOptions.appendChild(data.fileArrayList[i]);
                 var option = document.createElement('option');
                
                option.innerHTML = data.fileArrayList[i];
                var option2 = document.createElement('option');
                option2.innerHTML = data.fileArrayList[i];
                gedcomViewerOptions.appendChild(option);
                addIndFileList.appendChild(option2);
            }
                let tempTableLength = 0;

             // for(i = 0; i < data.fileIndList[i].length; i++)
            // {
                let indInfo = JSON.parse(data.fileIndList[0]);
                // console.log("indinf is " + indInfo);
                for(let individuals of indInfo)
                {
                    // console.log("person name is : "+ individuals.givenName + " " + individuals.surname);
                    
                     var indRow = gedcomViewTableArray.insertRow(tempTableLength+1);
                var indCellOne = indRow.insertCell(0);
                var indCellTwo = indRow.insertCell(1);
                var indCellThree = indRow.insertCell(2);
                var indCellFour = indRow.insertCell(3);
                // // // cellOne.innerHTML += ('<a href="/uploads/simpleValid.ged">simpleValid.ged</a>');
                indCellOne.innerHTML += (individuals.givenName);
                // indCellOne.innerHTML += ('test');

                indCellTwo.innerHTML += (individuals.surname);
                indCellThree.innerHTML += (individuals.gender);
                indCellFour.innerHTML += (individuals.familyCount);
                // // cellFive.innerHTML += (fileInfo.submitterName);

                // }
                tempTableLength += 1;
            }
    //         $( "<div>" )
    // .append(data.fileArrayList )
    // .appendTo( "#statusBox" );

            //We write the object to the console to show that the request was successful
            console.log(data.name); 
        },
        fail: function(error) {
            
            // Non-200 return, do something with error
            console.log(error); 
        }
    });

    // Event listener form replacement example, building a Single-Page-App, no redirects if possible
    $('form').submit(function(e){
        // console.log(e);
        if(e.currentTarget.id != 'uploadForm')
        {
            e.preventDefault();
            switch(e.currentTarget.id) {
                case 'addIndForm':
                    //convert boxes into json, use jsontoInd to get individual object
                    //use individual object to call insertIndividual
                    // console.log("add form is targeted");
                    $( "<div>" )
                     .append( e.target[0].value + " " + e.target[1].value + " has been added to file: " + e.target[4].value + "\n" )
                    .appendTo( "#statusBox" );
                    // console.log(e.target[2].value);
                    document.getElementById('addModal').style.display = "none";
                   var myJSON = {name: e.target[4].value, givenName: e.target[0].value ,surname: e.target[1].value};
                    var strJSON = encodeURIComponent(JSON.stringify(myJSON));

                    // $(document).ready(function() {
    // On page-load AJAX Example
    $.ajax({
        type: 'get',            //Request type
        dataType: 'JSON',
        
        // data: {surname:"\"" + e.target[0].value + "\"", givenName:"\"" + e.target[1].value + "\""},       //Data type - we will use JSON for almost everything 
        url: '/create/' + strJSON, 
        // data: strJSON,  //The server endpoint we are connecting to
        success: function (data) {
    // //           Do something with returned object
    // //             Note that what we get is an object, not a string, 
    // //             so we do not need to parse it on the server.
    // //             JavaScript really does handle JSONs seamlessly
            


    // //         //We write the object to the console to show that the request was successful
            console.log("yes" + data.name); 
        },
        fail: function(error) {
            
    // //         // Non-200 return, do something with error
            console.log(error + " no"); 
        }
    });

                    break;
                case 'createForm':
                    // console.log("create form is uploaded");
                      $( "<div>" )
                     .append( e.target[0].value + " " + e.target[1].value + " has been added to file: " + e.target[4].value + "\n" )
                    .appendTo( "#statusBox" );
                    // console.log(e.target[2].value);
                    // document.getElementById('addModal').style.display = "none";
                   var myJSON = {name: e.target[4].value, source: e.target[0].value ,gedcVersion: e.target[1].value, encoding: e.target[2].value, subName: e.target[3].value, subAddress: e.target[4].value};
                    var strJSON = encodeURIComponent(JSON.stringify(myJSON));
                    document.getElementById('createModal').style.display = "none";
                     $.ajax({
                            type: 'get',            //Request type
                            dataType: 'JSON',
                            
                            // data: {surname:"\"" + e.target[0].value + "\"", givenName:"\"" + e.target[1].value + "\""},       //Data type - we will use JSON for almost everything 
                            url: '/add/' + strJSON, 
                            // data: strJSON,  //The server endpoint we are connecting to
                            success: function (data) {
                        // //         //We write the object to the console to show that the request was successful
                                console.log("yes" + data.name); 
                            },
                            fail: function(error) {
                                
                        // //         // Non-200 return, do something with error
                                console.log(error + " no"); 
                            }
                        });
                    break;

                case 'signInForm':
                 document.getElementById('signInModal').style.display = "none";
                console.log('fuck me');
                console.log(e.target[2].value);
                var myJSON = {username: e.target[0].value, password: e.target[1].value ,database: e.target[2].value};
                var strJSON = encodeURIComponent(JSON.stringify(myJSON));
               
               console.log(myJSON);
                $.ajax({
                        type: 'get',            //Request type
                        dataType: 'JSON',
                        
                        // data: {surname:"\"" + e.target[0].value + "\"", givenName:"\"" + e.target[1].value + "\""},       //Data type - we will use JSON for almost everything 
                        url: '/signIn/' + strJSON, 
                        // data: strJSON,  //The server endpoint we are connecting to
                        success: function (data) {
                    // //           Do something with returned object
                    // //             Note that what we get is an object, not a string, 
                    // //             so we do not need to parse it on the server.
                    // //             JavaScript really does handle JSONs seamlessly
                            


                    // //         //We write the object to the console to show that the request was successful
                            console.log("yes" + data.name); 
                        },
                        fail: function(error) {
                            
                    // //         // Non-200 return, do something with error
                            console.log(error + " no"); 
                        }
                    });
                    break;
                default:
                console.log("default bitches");
                    break;
            }
        }
        $.ajax({

        });
    // //     // console.log("hi");
    });



    // document.getElementById('testButton').onclick = function() {
    //     console.log("end submit");
    // }

    // document.getElementById('getDate').onclick = function () {
                // $('#data1').html("Current date is "+getCurrentDate());
                // console.log("Dynamic stuff happened");
            // };

     $(document).on('change','#gedcomViewFileList',function(){
               // alert("PROBANDO");
               var gedcomViewFileList = document.getElementById('gedcomViewFileList');
               console.log(gedcomViewFileList.value);
                   $.ajax({
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/uploads/',   //The server endpoint we are connecting to
            success: function (data) {
                var gedcomViewTableArray = document.getElementById('gedcomTable');
                for(i = 1; i < gedcomViewTableArray.rows.length + 1; i++)
                {
                    var deleteRow = gedcomViewTableArray.deleteRow(i);
                    // var deleteCellOne = deleteRow.deleteCell(0);
                    // var deleteCellTwo = deleteRow.deleteCell(1);
                    // var deleteCellThree = deleteRow.deleteCell(2);
                    // var deleteCellFour = deleteRow.deleteCell(3);
                }
                console.log("length of table is " + gedcomViewFileList.value);
                var tempInt = 0;
                for(i = 0; i < data.fileArrayList.length; i++)
                {
                    if(data.fileArrayList[i] == gedcomViewFileList.value)
                    {
                        console.log('found a match with the two vals:' + data.fileArrayList[i] + gedcomViewFileList.value);
                        tempInt = i;
                        break;
                    }
                }
                let tempTableLength = 0;
                let indInfo = JSON.parse(data.fileIndList[tempInt]);
                console.log("indinf is " + tempInt);
                for(let individuals of indInfo)
                {
                    console.log("person name is : "+ individuals.givenName + " " + individuals.surname);
                    
                     var indRow = gedcomViewTableArray.insertRow(tempTableLength + 1);
                var indCellOne = indRow.insertCell(0);
                var indCellTwo = indRow.insertCell(1);
                var indCellThree = indRow.insertCell(2);
                var indCellFour = indRow.insertCell(3);
                // // // var cellFive= newRow.insertCell(4);
                // // // var cellSix = newRow.insertCell(5);
                // // // var cellSeven = newRow.insertCell(6);
                // // // var cellEight = newRow.insertCell(7);
                // // // testCell.innerHTML("hello");
                // // // cellOne.innerHTML += ('<a href="/uploads/simpleValid.ged">simpleValid.ged</a>');
                indCellOne.innerHTML += (individuals.givenName);
                // indCellOne.innerHTML += ('test');

                indCellTwo.innerHTML += (individuals.surname);
                indCellThree.innerHTML += (individuals.gender);
                indCellFour.innerHTML += (individuals.familyCount);
                // // cellFive.innerHTML += (fileInfo.submitterName);
                // // cellSix.innerHTML += (fileInfo.submitterAddress);
                // // cellSeven.innerHTML += (fileInfo.totalIndividuals);
                // // cellEight.innerHTML += (fileInfo.totalFamilies);
                // // gedcomViewerOptions.appendChild(data.fileArrayList[i]);
                //  // var option = document.createElement('option');
                
                // // option.innerHTML = data.fileArrayList[i];
                // // var option2 = document.createElement('option');
                // // option2.innerHTML = data.fileArrayList[i];
                // // gedcomViewerOptions.appendChild(option);
                // }
                tempTableLength += 1;
            }
                // console.log(data);
            },
                fail: function(error) {
            
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
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

     var createModal = document.getElementById('createModal');
    var createBtn = document.getElementById("createSimpleGedcom");
    var createSpan = document.getElementById("createClose");
    createBtn.onclick = function() {
        console.log("hello there");
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

    var uploadModal = document.getElementById('uploadModal');
    var uploadBtn = document.getElementById("uploadFile");
    var uploadSpan = document.getElementById("uploadClose");
    // var uploadSubmit = document.getElementById("uploadSubmit");
    uploadBtn.onclick = function() {
        // console.log("something");
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
    // var testButton = document.getElementById('testButton');

    // testButton.onclick = function() {
    //     // console.log("what");
    //      $( "<div>" )
    // .append( "Status\n" )
    // .appendTo( "#statusBox" );
    // }
    document.getElementById('clearButton').onclick = function() 
    {
        document.getElementById("statusBox").text=" ...";
        // $('#statusBox').val('');
        // console.log("end submit");
    }

    // var createModal = document.getElementById('createModal');
    // var createBtn = document.getElementById("createSimpleGedcom");
    // var createSpan = document.getElementById("createClose");
    // createBtn.onclick = function() {
    //     console.log("hello there");
    //     createModal.style.display = "block";
    // }

    // createSpan.onclick = function() {
    //     createModal.style.display = "none";
    // }

    // window.onclick = function(event) {
    //     if (event.target == createModal) {
    //         createModal.style.display = "none";
    //     }
    // }

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

    var signInModal = document.getElementById('signInModal');
    var signInBtn = document.getElementById("signInButton");
    var signInSpan = document.getElementById("signInClose");
    signInBtn.onclick = function() {
        signInModal.style.display = "block";
    }

    signInSpan.onclick = function() {
        signInModal.style.display = "none";
    }

    window.onclick = function(event) {
        if (event.target == signInModal) {
            signInModal.style.display = "none";
        }
    }

});
