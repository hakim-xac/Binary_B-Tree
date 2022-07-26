#pragma once

namespace KHAS {

    // тип дерева
    enum class TypeTree {
        AVL, DBD
    };

    // используемые команды в программе
    enum class InputCommand {
        NoCommand
        , Exit
        , ErrorCommands
        , Print
    };

    // Тип поворотов в АВЛ дереве
    enum class RotationTree {
        Left
        , Right
        , LeftRight
        , RightLeft
    };

    enum class InsertTypeInBTree {
        Begin
        , Next
    };

}