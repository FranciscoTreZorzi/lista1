#include "Scene4.h"

CScene4::CScene4()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 0.1f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	fRotY = 0.0f;

	fPosX = 0.0f;
	fPosY = 0.0f;
	fPosZ = 0.0f;

	rot = 0;
	valorRot = 1;


	for (int i = 0; i < 38; i++)
		faceColor[i] = { (rand() % 255), (rand() % 255), (rand() % 255) };

}


CScene4::~CScene4(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}
}




int CScene4::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter

	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	// Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glColor4ub(255, 255, 255, 255);

	// Desenha o chão
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-10.0f, 0.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();

	glColor4ub(240, 240, 255, 255);

	glPushMatrix();
	// Cria primeira bola do boneco de neve
	glTranslatef(5.0f, 0.25f, 4.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glRotatef(rot, 0.0f, 0.0f, 1.0f);
	glScalef(0.25f, 0.25f, 0.25f);
	auxSolidSphere(2.0);

	// Cria segunda bola do boneco de neve
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	auxSolidSphere(2.0);

	// Cria os botões do boneco de neve
	glPushMatrix();
	glColor4ub(230, 90, 60, 255);
	glTranslatef(0.0f, -0.25f, 2.0f);
	auxSolidSphere(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.75f, 2.0f);
	auxSolidSphere(0.25);
	glPopMatrix();

	// Cria a terceira bola do boneco de neve
	glColor4ub(240, 240, 255, 255);
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	auxSolidSphere(2.0);

	// Cria o nariz e os olhos do boneco de neve
	glPushMatrix();
	glColor4ub(50, 50, 50, 255);
	glTranslatef(-0.5f, 0.75f, 2.0f);
	auxSolidSphere(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 0.75f, 2.0f);
	auxSolidSphere(0.25);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(235, 165, 50, 255);
	glTranslatef(0.0f, -0.25f, 1.5f);
	auxSolidCone(0.5f, 2.0f);
	glPopMatrix();

	// Desenha o chapeu do boneco de neve
	glPushMatrix();
	glColor4ub(60, 60, 145, 255);
	glTranslatef(0.0f, 1.75f, 0.0f);
	glScalef(1.0f, 0.0f, 1.0f);
	auxSolidSphere(2.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.50f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	auxSolidCylinder(1.5, 1.0);
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glScalef(0.75f, 0.0f, 0.75f);
	auxSolidSphere(2.0f);
	glPopMatrix();
	glPopMatrix();
	

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// Desenha a floresta
	DrawFlorest();
	

	rot += valorRot;

	if (rot == 45) {
		valorRot = -1;
	}
	else if (rot == -45) {
		valorRot = 1;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 150, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));

	glRasterPos2f(10.0f, 100.0f);
	pTexto->glPrint("fRot: %.1f ", fRotY);




	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene4::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene4::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}


	if (GetKeyState(VK_LEFT) & 0x80)
		fPosX -= 0.1f;
	if (GetKeyState(VK_RIGHT) & 0x80)
		fPosX += 0.1f;
	if (GetKeyState(VK_UP) & 0x80)
		fPosZ -= 0.1f;
	if (GetKeyState(VK_DOWN) & 0x80)
		fPosZ += 0.1f;
	if (GetKeyState(VK_PRIOR) & 0x80)
		fPosY += 0.1f;
	if (GetKeyState(VK_NEXT) & 0x80)
		fPosY -= 0.1f;


}

void CScene4::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene4::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void CScene4::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CScene4::DrawTree(float px, float py, float pz, float sx, float sy, float sz)
{
	//Define a posição da arvore
	glTranslatef(px, py, pz);

	// Desenha o tronco da arvore
	glColor4ub(80, 60, 5, 255);
	// Define a escala da arvore
	glScalef(sx, sy, sz);
	auxSolidCylinder(0.25, 1.0);

	// Desenha as folhas da arvore
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glColor4ub(40, 110, 40, 255);
	glScalef(1.0f, 1.0f, 1.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	auxSolidCone(1.0f, 2.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.25f);
	glColor4ub(40, 110, 40, 255);
	auxSolidCone(1.0f, 2.0f);
	glPopMatrix();
	glPopMatrix();
}

void CScene4::DrawFlorest()
{
	glPushMatrix();
	DrawTree(-5.0f, 0.0f, -4.0f, 1.0f, 2.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(7.0f, 0.0f, 8.0f, 1.0f, 3.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(-3.0f, 0.0f, 1.5f, 1.0f, 2.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(-8.0f, 0.0f, -8.0f, 1.5f, 3.0f, 1.5f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(-7.0f, 0.0f, 6.0f, 2.0f, 4.0f, 2.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(6.0f, 0.0f, -6.0f, 1.0f, 2.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(9.0f, 0.0f, -4.0f, 0.5f, 1.0f, 0.5f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(3.0f, 0.0f, -2.0f, 2.0f, 5.0f, 2.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(2.0f, 0.0f, 3.0f, 1.0f, 2.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(0.5f, 0.0f, 7.0f, 0.25f, 0.5f, 0.25f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(-1.5f, 0.0f, -7.5f, 1.0f, 2.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(-1.5f, 0.0f, 5.0f, 0.75f, 2.0f, 0.75f);
	glPopMatrix();
}