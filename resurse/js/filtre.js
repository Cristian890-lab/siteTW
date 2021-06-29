window.onload=function() {
    //filtru
    let btn = document.getElementById("filtru");
    btn.onclick = function () {
        let produse = document.querySelectorAll('article[class^="produs_"]');
        let categorie = document.getElementById("inp-categorie").value
        for (let i = 0; i < produse.length; i++) {
            produse[i].style.display = "none";

            //search = conditia1 (pentru nume)
            let titlu = produse[i].getElementsByClassName("nume")[0].innerHTML.toLowerCase();
            let search = null;
            if (document.getElementById("i_text") != null) {
                search = document.getElementById("i_text").value.toLowerCase();
            }
            var conditie1 = (titlu.search(search) != -1 || search == null);

            //range = conditia2 (pentru pret)
            let pretmax = parseInt(document.getElementById("i_range").value);
            let pret = produse[i].getElementsByClassName("pret")[0].innerHTML;
            var conditie2 = pret < pretmax;

            //checkbox = conditia3 (pentru stock)
            var conditie3 = 0;
            let stock = produse[i].getElementsByClassName("stock")[0].innerHTML;
            if ((document.getElementById("i_check1").checked && stock == document.getElementById("i_check1").value) || (document.getElementById("i_check1").checked != true)) {
                conditie3 = 1;
            }

            //radiobuttons = conditia4 (pentru marca)
            let tip = produse[i].getElementsByClassName("tip")[0].innerHTML;
            var radiobuttons = document.getElementsByName("gr_rad");
            let sir;
            for (let rad of radiobuttons) {
                console.log(rad.value);
                if (rad.checked) {
                    sir = rad.value;
                    break;
                }
            }
            var conditie4 = (tip == sir || sir == "toate");

            //textarea = conditie5 (pentru descriere)
            let des = produse[i].getElementsByClassName("descriere")[0].innerHTML.toLowerCase();
            let chei = document.getElementById('i_textarea').value.toLowerCase().split(" ");
            let conditie5 = false;
            let nr = 0;
            for (let che of chei) {
                if (des.search(che.substr(1)) != -1) {
                    conditie5 = true;
                }
            }

            //select = conditie6 (pentru color)
            let categorieArt = produse[i].getElementsByClassName("culoare")[0].innerHTML.toLowerCase();
            var conditie6 = (categorieArt == categorie || categorie == "all");

            //select multiplu = conditie7 (pentru masuratori)
            let optiuni = document.getElementById("i_sel_multiplu").options;
            let mar = produse[i].getElementsByClassName("dimensiuni")[0].innerHTML;
            let marime;
            let conditie7 = false;
            if (mar == null || mar == "" || mar == " ") {
                marime = 4;
            }
            if (mar.includes(',')) {
                marime = mar.match(/,/g).length;
            }
            if (!mar.includes(',') && mar != null && mar != "" && mar != " ") {
                marime = 0;
            }
            for (let opt of optiuni) {
                if (opt.selected) {
                    if (opt.value == "all") {
                        conditie7 = false;
                    }
                    if (marime != opt.value) {
                        conditie7 = true;
                    }
                }
            }

            //conditia finala
            ConditieTotala = conditie1 && conditie2 && conditie3 && conditie4 && conditie5 && conditie6 && conditie7;
            if (ConditieTotala)
                produse[i].style.display = "block";
        }
    }
    //calcul
            btn = document.getElementById("calcul")
            btn.onclick= function(){

                let produse=document.querySelectorAll('article[class^="produs_"]');
                sumaArt=0;
                for (let prod of produse){
                    sumaArt+= parseInt(prod.getElementsByClassName("pret")[0].innerHTML);
                }
                let infoSuma=document.createElement("p");//<p></p>
                infoSuma.innerHTML="Total: "+sumaArt+" RON";//<p>...</p>
                infoSuma.className="info-produse";
                let p=document.getElementById("p-suma")
                p.parentNode.insertBefore(infoSuma,p.nextSibling);
                setTimeout(function(){infoSuma.remove()}, 4000);
            }

    btn=document.getElementById("resetare");
    btn.onclick=function(){
        let produse=document.querySelectorAll('article[class^="produs_"]');
        for (let prod of produse){
            prod.style.display="block";
        }
        document.getElementById('i_text').value="";
        document.getElementById('i_range').value=4000;
        document.getElementById('i_check1').checked=0;
        document.getElementById('inp-categorie').value="all";
        let radiobuttons=document.getElementsByName("gr_rad");
        for(let rad of radiobuttons){
            if(rad.value=="toate"){
                rad.checked=1;
            }
        }
        let optiuni=document.getElementById("i_sel_multiplu").options;
        for(let opt of optiuni){
            console.log(opt.value);
            if (opt.value == "all"){
                opt.selected=1;
            }
            else
            {
                opt.selected=0;
            }

        }
        document.getElementById('i_textarea').value="";
    }



    function sortArticole(factor){
        let produse = document.querySelectorAll('article[class^="produs_"]');
        let arrayProduse=Array.prototype.slice.call(produse);
        arrayProduse.sort(function(art1,art2){
            let pret1=art1.getElementsByClassName("pret")[0].innerHTML;
            let pret2=art2.getElementsByClassName("pret")[0].innerHTML;
            let marca1=art1.getElementsByClassName("tip")[0].innerHTML;
            let marca2=art2.getElementsByClassName("tip")[0].innerHTML;
            let rez = factor*(pret1-pret2);
            if (rez==0){
                return factor*marca1.localeCompare(marca2);
            }
            return rez;

        });
        console.log(arrayProduse);
        for (let prod of arrayProduse){
            prod.parentNode.appendChild(prod);
        }
    }
    
    btn=document.getElementById("sortCrescNume");
    btn.onclick=function(){
        sortArticole(1);
    }
    btn=document.getElementById("sortDescrescNume");
    btn.onclick=function(){
        sortArticole(-1);
    }
}

