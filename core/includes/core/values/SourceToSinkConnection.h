#pragma once
#include <core/core.h>
#include <core/values/values.h>
#include <core/values/Connection.h>

NS_BEGIN(CORE_VALUES_NAMESPACE)

  class SourceToSinkConnection : public Connection{
  protected:
    virtual bool isDirty(std::shared_ptr<ISource> source, std::shared_ptr<ISink> sink){ return true; }
  public:
    
    typedef std::weak_ptr<ISink> sink_type;
    typedef std::weak_ptr<ISource> source_type;

    bool sync() override{
      auto source = _source.lock();
      if (!source)return false;
      auto sink = _sink.lock();
      if (!sink)return false;

      if (!isDirty(source, sink)){ return true; }

      auto arg = source->produce();
      sink->consume(arg);

      return true;
    }
    virtual bool disconnect()override{
      _sink = sink_type();
      _source = source_type();
      return true;
    }
    virtual bool connect(connectable_type from, connectable_type to) override{

      auto source = std::dynamic_pointer_cast<ISource>(from);
      if (!source)return false;
      auto sink = std::dynamic_pointer_cast<ISink>(to);
      if (!sink)return false;
      _sink = sink;
      _source = source;
      return true;
    }
  private:
    sink_type _sink;
    source_type _source;
  };

  /// connects a source to a sink via a simple manual connection
  inline auto connect(std::shared_ptr<ISource> from, std::shared_ptr<ISink> to)-> std::shared_ptr<SourceToSinkConnection>{
    auto connection = std::make_shared<SourceToSinkConnection>();
    if (!connection->connect(from, to))return std::shared_ptr<SourceToSinkConnection>();
    return connection;
  }
NS_END(CORE_VALUES_NAMESPACE)
