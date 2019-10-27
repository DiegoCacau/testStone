# testStone

Projeto de aplicação de estágio para a Stone. 


## Antes de usar

Antes de rodar o projeto, o usuário deverá editar o arquivo ```secretkeys.h.example```, preenchendo com Client ID e Client Secret, obtidos na página de desenvolvedor do Spotify, e em seguida salvar o arquivo com o nome de ```secretkeys.h```.

## Como usar

Ao iniciar a aplicação uma tela com botão de login será aberta, ao clicar o usuário será redirecionado para a tela de login do Spotify. Após o usuário autorizar o uso de seus dados pela aplicação, será aberta a aplicação principal.

O primeiro passo é criar uma playlist, ao menos.
Em seguida o usuário deverá selecionar a playlist que deseja editar e somente então o usuário poderá buscar por músicas e adicioná-las a sua playlist.



## Considerações finais

### Pontos Positivos do Teste
- A API do Spotify possui vários exemplos disponíveis, o que facilitou bastante;
- Tive que aprender como fazer os testes da parte gráfica, o que me lembrou um pouco o Selenium, mas com uma pitada de dificuldade para entender o ínicio do processo;
- Matar a saudade de desenvolver em C++;

### Pontos Não Tão Positivos do Teste
- Apesar de já ter lido bastante sobre testes, nunca tive que fazê-los em "produção" e sinto que me enrolei um pouco com os testes da aplicação gráfica;
- Minha falta de atenção, que fez com que eu só percebesse que tinha nomeado a classe como "Spofity" quando já estava quase acabando, o que me levou a decisão de adotar esse nome;
- Eu ter gasto quase 2 dias lembrando como escrever códigos em C++ e Qt; 