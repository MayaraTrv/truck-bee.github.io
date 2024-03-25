document.getElementById('btnAbrir').addEventListener('click', function() {
  document.getElementById('caixaTexto').style.display = 'block';
});

document.getElementById('btnAbrir2').addEventListener('click', function() {
  document.getElementById('caixaTexto2').style.display = 'block';
});

document.getElementById('btnAbrir3').addEventListener('click', function() {
  document.getElementById('caixaTexto3').style.display = 'block';
});

document.getElementById('btnAbrir4').addEventListener('click', function() {
  document.getElementById('caixaTexto4').style.display = 'block';
});

document.getElementById('btnAbrir5').addEventListener('click', function() {
  document.getElementById('caixaTexto5').style.display = 'block';
});


function fecharCaixa(idCaixa) {
  document.getElementById(idCaixa).style.display = 'none';
}