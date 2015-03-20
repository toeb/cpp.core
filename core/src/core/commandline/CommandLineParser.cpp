#include <core/commandline/CommandLineParser.h>

NS_USE(CORE_NAMESPACE);
NS_USE(CORE_NAMESPACE)::commandline;

CommandLineParser::CommandLineParser(const int argc, const char *const* argv){
  parse(argc,argv);
}

void CommandLineParser::parse(const int argc, const char *const* argv){

  _tokens.clear();
  setExecutablePath("");
  if(!argc)return;
  setExecutablePath(*argv);
  for(int i=1; i < argc; i++){
    _tokens.push_back(argv[i]);
  }


}

auto CommandLineParser::DefineArgument(const std::string & name,const std::string & description, const std::string & alias)->DefinitionPointer{
  auto definition=std::shared_ptr<CommandLineArgumentDefinition>(new CommandLineArgumentDefinition(name,description,alias));        
  Definitions()|=definition;
  return definition;
}
auto CommandLineParser::Definition(const std::string & nameOrAlias)->DefinitionPointer{
  return Definitions().first([&](DefinitionPointer definition){return definition->isIdentifiedBy(nameOrAlias);});
}


auto CommandLineParser::Argument(CommandLineArgumentDefinition & definition)->ArgumentPointer{
  CommandLineArgument arg(definition);

  auto it = _tokens.begin();
  auto end = _tokens.end();
  std::vector<std::string> tokens;
  bool definitionStarted = false;
  while(it!=end){
    if(definition.isIdentifiedBy(*it)){
      definitionStarted = true;
    }else if(definitionStarted){
      if(Definition(*it)){
        break;
      }
      tokens.push_back(*it);
    }
    it++;
  }
  if(it==end&&!definitionStarted)return ArgumentPointer();

  arg.Tokens() =tokens;

  return ArgumentPointer(new CommandLineArgument(arg));
}

auto CommandLineParser::Argument(const std::string & nameOrAlias)->ArgumentPointer{
  auto definition =Definition(nameOrAlias);
  if(!definition)return ArgumentPointer();
  return Argument(*definition);

}


