#include "target.h"

Target:: Target(QOpenGLWidget * _glWidget)
{
    glWidget = _glWidget;
    glWidget->makeCurrent();
    initializeOpenGLFunctions();
    shaderOK = false;
    vboOK = false;
    loaded = false;

}
Target::~Target()
{
    destroyVBOs();
    destroyShaders();
}

void Target::destroyVBOs()
{
    // makeCurrent ();
    glDeleteBuffers(1 , &vboVertices);
    glDeleteBuffers (1 , &vboIndices);
    glDeleteVertexArrays (1 , &vao);
    vboVertices = 0;
    vboIndices = 0;
    vao = 0;
}

void Target::destroyShaders()
{
    glDeleteProgram(shaderProgram);
}

void Target::createVBOs()
{
    glWidget->makeCurrent();
    destroyVBOs();
    glGenVertexArrays (1 , &vao);
    glBindVertexArray(vao);
    glGenBuffers(1 , &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(QVector4D),vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray (0);
    glGenBuffers(1 , &vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,numFaces * 3 * sizeof(unsigned int), indices.get() , GL_STATIC_DRAW);

    vboOK = true;


}

void Target::createShaders()
{
    // makeCurrent ();
    destroyShaders();
    QString vertexShaderFile (":/shaders/vtarget.glsl");
    QString fragmentShaderFile (":/shaders/ftarget.glsl");

    QFile vs (vertexShaderFile);
    QFile fs (fragmentShaderFile);

    vs.open(QFile::ReadOnly | QFile::Text);
    fs.open(QFile::ReadOnly | QFile::Text);

    QTextStream streamVs(&vs),streamFs(&fs);

    QString qtStringVs = streamVs.readAll();
    QString qtStringFs = streamFs.readAll();

    std::string stdStringVs = qtStringVs.toStdString();
    std::string stdStringFs = qtStringFs.toStdString();

    // Create an empty vertex shader handle
    GLuint vertexShader = 0;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    const GLchar * source = stdStringVs.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv (vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog (maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        qDebug ("% s", &infoLog[0]);
        glDeleteShader(vertexShader);
        return;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = 0;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std :: string â€™s . c_str is NULL character terminated .
    source = stdStringFs.c_str();
    glShaderSource (fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog (maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        qDebug ("% s", &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader (vertexShader);
        return;
    }

    shaderProgram = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader (shaderProgram, fragmentShader);

    // Link our program
    glLinkProgram(shaderProgram);

    // Note the different functions here : glGetProgram * instead of  glGetShader *.
    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *) &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv ( shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog (shaderProgram, maxLength, &maxLength, &infoLog[0]);
        qDebug ("% s", &infoLog[0]);
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    vs.close();
    fs.close();

    shaderOK = true;

}

void Target::drawTarget()
{
    loaded = false;
    targetMatrix.setToIdentity();
    targetMatrix.scale(invDiag, invDiag, invDiag);
    targetMatrix.translate(-midPoint);

    glBindVertexArray(vao);
    glUseProgram(shaderProgram);
    GLuint locTargetMatrix = glGetUniformLocation(shaderProgram,"target");
    glUniformMatrix4fv(locTargetMatrix, 1, GL_FALSE, targetMatrix.data());
    glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_INT, 0);
    loaded = true;
}

void Target::readOFFFile (QString const & fileName)
{
    std::ifstream stream;
    stream.open(fileName.toUtf8(), std::ifstream::in);
    if (!stream.is_open())
    {
        qWarning("Cannot open file .");
        return;
    }
    std::string line;
    stream >> line;
    stream >> numVertices >> numFaces >> line;
    vertices = std::make_unique <QVector4D[]>(numVertices);
    indices = std::make_unique <unsigned int []>( numFaces * 3);

    if ( numVertices > 0)
    {
        float minLim = std::numeric_limits <float>::lowest();
        float maxLim = std::numeric_limits <float>::max();
        QVector4D max(minLim, minLim, minLim, 1.0);
        QVector4D min(maxLim, maxLim, maxLim, 1.0);
        for (unsigned int i = 0; i < numVertices ; ++i)
            {
                float x , y , z;
                stream >> x >> y >> z;
                max.setX(std::max(max.x(), x));
                max.setY(std::max(max.y(), y));
                max.setZ(std::max(max.z(), z));
                min.setX(std::min(min.x(), x));
                min.setY(std::min(min.y(), y));
                min.setZ(std::min(min.z(), z));
                vertices[i] = QVector4D (x , y , z , 1.0);
            }
        this->midPoint = QVector3D(( min + max ) * 0.5);
        this->invDiag = 2.0 / (max - min).length();

        for (unsigned int i = 0; i < numFaces ; ++ i)
            {
                unsigned int a , b , c;
                stream >> line >> a >> b >> c;
                indices [i * 3 + 0] = a;
                indices [i * 3 + 1] = b;
                indices [i * 3 + 2] = c;
            }
        stream.close();
        createShaders();
        createVBOs ();
      }
}