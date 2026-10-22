namespace
{
	using RemoveSubtitle_t = void(RE::SubtitleManager*, RE::TESObjectREFR*);
	REL::Relocation<RemoveSubtitle_t> RemoveSubtitle{ RELOCATION_ID(51754, 52627) };  // SubtitleManager::RemoveSubtitle

	// engine ends the line on demotion but leaves the subtitle for a low process update that comes hours later
	struct MovetoLow
	{
		static bool thunk(RE::Character* a_this)
		{
			const auto result = func(a_this);
			RemoveSubtitle(RE::SubtitleManager::GetSingleton(), a_this);
			return result;
		}
		static inline REL::Relocation<decltype(thunk)> func;
	};

	struct MovetoMiddleLow
	{
		static bool thunk(RE::Character* a_this)
		{
			const auto result = func(a_this);
			RemoveSubtitle(RE::SubtitleManager::GetSingleton(), a_this);
			return result;
		}
		static inline REL::Relocation<decltype(thunk)> func;
	};
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
	SKSE::Init(skse);
	REL::Relocation<std::uintptr_t> vtbl{ RE::Character::VTABLE[0] };
	MovetoLow::func = vtbl.write_vfunc(0xF2, MovetoLow::thunk);  // Character::MovetoLow
	MovetoMiddleLow::func = vtbl.write_vfunc(0xF3, MovetoMiddleLow::thunk);  // Character::MovetoMiddleLow
	return true;
}